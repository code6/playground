CREATE TABLE `yqk_city` (
  `id` int(10) unsigned NOT NULL auto_increment COMMENT ' 城市ID ',
  `fetch_url` varchar(200) NOT NULL DEFAULT '' COMMENT '抓取链接',
  `name` varchar(32) NOT NULL DEFAULT '' COMMENT '城市名',
  `status` tinyint(1) unsigned NOT NULL COMMENT '抓取状态 0-新建 1-失效',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='yqk城市列表';

CREATE TABLE `yqk_city_drugcompany_page` (
  `id` int(10) unsigned NOT NULL auto_increment COMMENT ' 城市列表页ID ',
  `fetch_url` varchar(200) NOT NULL DEFAULT '' COMMENT '抓取链接',
  `cityid` int(10) unsigned NOT NULL  COMMENT '城市ID',
  `status` tinyint(1) unsigned NOT NULL COMMENT '抓取状态 0-新建 1-失效',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`fetch_url`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='yqk城市药企页面';

CREATE TABLE `yqk_drugcompany` (
  `id` int(10) unsigned NOT NULL auto_increment COMMENT ' 药企ID ',
  `identity` varchar(100) NOT NULL DEFAULT '' COMMENT '药企编号 ',
  `fetch_url` varchar(200) NOT NULL DEFAULT '' COMMENT '药企链接',
  `brand_url` varchar(200) NOT NULL DEFAULT '' COMMENT '药企品牌链接',
  `brandlist` text NOT NULL COMMENT '品牌信息，按逗号分割',
  `name` varchar(200) NOT NULL DEFAULT '' COMMENT '药企名称',
  `email` varchar(200) NOT NULL DEFAULT '' COMMENT '药企电子邮箱',
  `contact` varchar(200) NOT NULL DEFAULT '' COMMENT '联系人',
  `faxphone` varchar(200) NOT NULL DEFAULT '' COMMENT '传真电话',
  `phone` varchar(200) NOT NULL DEFAULT '' COMMENT '联系电话',
  `address` varchar(1000) NOT NULL DEFAULT '' COMMENT '药企地址',
  `postcode` varchar(1000) NOT NULL DEFAULT '' COMMENT '邮政编码',
  `cityid` int(10) unsigned NOT NULL  COMMENT '城市ID',
  `basicinfo` text NOT NULL COMMENT '基本信息',
  `status` tinyint(1) unsigned NOT NULL COMMENT '抓取状态 0-新建 1-失效 2-完成 3-生成子任务完毕',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`identity`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='药企信息';

0 - 2 - 3
    |
    1

CREATE TABLE `yqk_drug_page` (
  `id` int(10) unsigned NOT NULL auto_increment COMMENT ' 药品页ID ',
  `drugcompany_id` int(10) unsigned NOT NULL  COMMENT ' 药企ID ',
  `fetch_url` varchar(200) NOT NULL DEFAULT '' COMMENT '药品页链接',
  `status` tinyint(1) unsigned NOT NULL COMMENT '抓取状态 0-新建 1-失效',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`fetch_url`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='药企信息';

CREATE TABLE `yqk_drug` (
  `id` int(10) unsigned NOT NULL auto_increment COMMENT ' 药品ID ',
  `identity` varchar(100) NOT NULL DEFAULT '' COMMENT '药品标示符 ',
  `drugcompany_id` int(10) unsigned NOT NULL  COMMENT ' 药企ID ',
  `fetch_url` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品链接',
  `name` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品名称',
  `chemical` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品化学成分',
  `specification` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品规格',
  `usage` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品用法用量',
  `indication` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品功效主治',
  `expiretime` varchar(500) NOT NULL DEFAULT '' COMMENT '药品有效期',
  `company` varchar(1000) NOT NULL DEFAULT '' COMMENT '药品生产企业',
  `status` tinyint(1) unsigned NOT NULL COMMENT '抓取状态 0-新建 1-失效 2-完成',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`identity`),
  KEY (`drugcompany_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='药品信息';
