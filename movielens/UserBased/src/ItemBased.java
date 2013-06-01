
import java.io.*;
import java.util.*;

public class ItemBased {

  class Neighbor {
    public int id;
    public double sim;

    Neighbor(int id, double sim) {
      this.id = id;
      this.sim = sim;
    }
  }


  public final int MAX_USER = 1000;
  public final int MAX_ITEM = 2000;


  //用户物品打分训练数据
  public int[][] userItemTrainData;
  // 用户物品推荐打分
  public double[][] userItemRecommendData;

  //用户物品打分测试数据
  public int[][] userItemTestData;

  //是否有共同打分记录
  public boolean[][] commonUser;


  // 用户相似度
  public double[][] itemSim;

  //邻居数限制
  public int neighbourLimit;


  public ItemBased(String trainDataFile, String testDataFile, int neighbourLimit) {
    // trainDataFile 训练集文件
    // testDataFile  测试集文件

    userItemTrainData = loadData(trainDataFile);
    userItemTestData = loadData(testDataFile);
    this.neighbourLimit = neighbourLimit;

  }

  // 载入数据
  public int[][] loadData(String path) {
    int[][] ret = new int[MAX_USER][MAX_ITEM];

    try {
      BufferedReader in = new BufferedReader(new FileReader(path));
      String line;
      while ((line = in.readLine()) != null) {
        String[] arr = line.split("\t");
        int userid = Integer.parseInt(arr[0]);
        int itemid = Integer.parseInt(arr[1]);
        int rating = Integer.parseInt(arr[2]);

        if (!(1 <= rating && rating <= 5)) {
          throw new AssertionError();
        }

        ret[userid][itemid] = rating;
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
    } catch (IOException e) {
      e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
    }

    return ret;
  }


  public ArrayList<Integer> getCommonUserList(int ia, int ib) {
    //计算公共物品数组
    ArrayList<Integer> commonUserList = new ArrayList<Integer>();
    for (int k = 0; k < MAX_USER; k++) {
      if (userItemTrainData[k][ia] > 0 && userItemTrainData[k][ib] > 0) {
        commonUserList.add(k);
      }
    }
    return commonUserList;
  }

  public double PearsonCorrelationCoefficient(int ia, int ib) {
    // 公式参考: http://www.douban.com/note/208193209/

    ArrayList<Integer> commonUserList = getCommonUserList(ia, ib);

    // 如果没有公共物品, 相似度为0
    if (commonUserList.size() == 0) {
      return 0.0;
    }

    int n = commonUserList.size();

    double sum_xy, sum_x, sum_y, sum_x2, sum_y2;
    sum_xy = sum_x = sum_y = sum_x2 = sum_y2 = 0.0;

    for (Integer user : commonUserList) {
      int ra = userItemTrainData[user][ia];
      int rb = userItemTrainData[user][ib];
      sum_xy += ra * rb;
      sum_x += ra;
      sum_y += rb;
      sum_x2 += Math.pow(1.0 * ra, 2.0);
      sum_y2 += Math.pow(1.0 * rb, 2.0);
    }

    double denominator = Math.pow(sum_x2 - Math.pow(sum_x, 2.0) / n, 0.5) *
            Math.pow(sum_y2 - Math.pow(sum_y, 2.0) / n, 0.5);

    // demonminator 过小
    if (Math.abs(denominator) < 1e-7) {
      return 0.0;
    } else {
      return (sum_xy - (sum_x * sum_y) / n) / denominator;
    }
  }


  // 计算两两相似度
  public void calcSim() {
    commonUser = new boolean[MAX_ITEM][MAX_ITEM];
    itemSim = new double[MAX_ITEM][MAX_ITEM];
    for (int i = 0; i < MAX_ITEM; i++) {
      for (int j = i + 1; j < MAX_ITEM; j++) {
        commonUser[i][j] = commonUser[j][i] = getCommonUserList(i, j).size() > 0;
        if (commonUser[i][j]) {
          itemSim[i][j] = itemSim[j][i] = PearsonCorrelationCoefficient(i, j);
        }
      }
    }
  }

  public int[] computeNearestNeighbor(int userid, int itemid) {
    List<Neighbor> neighborList = new ArrayList<Neighbor>();
    for (int i = 0; i < MAX_ITEM; i++) {
      if (userItemTrainData[userid][i] > 0 && itemSim[itemid][i] > 0) {
        neighborList.add(new Neighbor(i, itemSim[itemid][i]));
      }
    }

    Collections.sort(neighborList, new Comparator<Neighbor>() {
      @Override
      public int compare(Neighbor o1, Neighbor o2) {
        if (o1.sim > o2.sim) return -1;
        if (o1.sim < o2.sim) return 1;
        return 0;
      }
    });

    int neighbourSize = Math.min(neighbourLimit, neighborList.size());

    int[] ret = new int[neighbourSize];
    for (int i = 0; i < neighbourSize; i++) {
      ret[i] = neighborList.get(i).id;
    }

    return ret;
  }

  public double recommend(int userid, int itemid) {

    double estimateScore = 0.0;

    int[] nearestNeighborList = computeNearestNeighbor(userid, itemid);
    // 将系数归一化
    double[] weightList = new double[nearestNeighborList.length];

    for (int k = 0; k < nearestNeighborList.length; k++) {
      weightList[k] = itemSim[itemid][nearestNeighborList[k]];
    }

    if (userItemTrainData[userid][itemid] > 0) {
      // 已经打分过就推荐同样的分数
      estimateScore = userItemTrainData[userid][itemid];
    } else {
      // 没有打分过的话就用最近邻居的分数来估算
      estimateScore = 0.0;

      double totalDistance = 0.0;

      for (int k = 0; k < nearestNeighborList.length; k++) {

        int score = userItemTrainData[userid][nearestNeighborList[k]];

        if (score > 0) {
          estimateScore += weightList[k] * score;
          totalDistance += weightList[k];
        }

      }

      if (Math.abs(totalDistance) < 1e-7) {
        estimateScore = 3;
      } else {
        estimateScore /= totalDistance;
      }

    }

    return estimateScore;
  }

  public void calcMAE() {
    int totalCase = 0;

    double error = 0.0;
    double squError = 0.0;
    for (int i = 0; i < MAX_USER; i++) {
      for (int j = 0; j < MAX_ITEM; j++) {
        if (userItemTestData[i][j] > 0) {
          totalCase += 1;
          double estimateScore = recommend(i, j);

          error += Math.abs(userItemTestData[i][j] - estimateScore);
          squError += Math.pow(userItemTestData[i][j] - estimateScore, 2.0);
        }
      }
    }
    double mae = error / totalCase;
    double rmse = Math.pow(squError / totalCase, 0.5);
    System.out.println("totalCase = " + totalCase + " MAE = " + mae + " RMSE = " + rmse);

  }

  public static void main(String[] args) {

    String basePath = "/Users/code6/git/playground/movielens/UserBased/src/ml-100k/";

    int neighbourLimit = 10;


    for (int testcase = 1; testcase <= 5; testcase++) {
      String trainDataFile = basePath + "u" + testcase + ".base";
      String testDataFile = basePath + "u" + testcase + ".test";

      System.out.println("Item Based, Test Case  = " + testcase + " neighbourLimit=" + neighbourLimit);

      ItemBased ub = new ItemBased(trainDataFile, testDataFile, neighbourLimit);
      // 计算用户相似度
      ub.calcSim();
      ub.calcMAE();

    }
  }
}
