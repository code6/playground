from OpenHiveClient import *
if __name__ == "__main__":
    serverConf = { 
        'port' : 6132,
        'host' : '10.64.14.213',
        }   
    client = OpenHiveClient(**serverConf)
    q = Query()
    q.query = "select * from dim.city limit 5"
    q.username = "normal_user"
    client.query(q)
    ret = client.fetchOne()
    print ret 
    ret = client.fetchAll(10)
    print ret 
    for l in ret:
            print l
