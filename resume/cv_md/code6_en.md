#Zhichun Wu 

* Email: <wzc1989@gmail.com>
* Phone: +86 18211154219 
* Blog: <http://code6.github.com>
* Github : <http://github.com/code6>
* Topcoder : [code6](http://community.topcoder.com/tc?module=MemberProfile&cr=22758532) 

##Background
I am a software engineer with interset in big data and algorithm. I enjoy building tools to simplify everyday job. I enjoy algorithm competitions and practice a lot at spare time. 

## Skill

* Use python / php / SQL in daily development
* Familar with data warehouse modeling, the design of ETL flow
* Have some experience in data platform components development(scheduler, ETL tool)
* Familar with hive, understand of hadoop ecosystem
* Familar with common data structure


## Experience

### meituan.com, Beijing, China

##### Software Engineer - July 2011 to Present

I 'm working at meituan data team, I focus on data warehouse/platform tools building. 

* ETL tool `sqlweaver` upgrade  
  `sqlweaver` is our data warehouse ETL tool. At first it only support mysql, I add different database supports by adding a concept called resouce handler and add support to hive and shard mysql table . I add another concept called action which enable loose ETL steps construct and code reuse, which works well for complex ETL tasks.
 
* Data synchronization Tool  
  I build a data synchronization tool base on our ETL tool `sqlweaver` which supports data sync between different type of database(mysql/hive). Users only need to fill in the source and target table info and it will do the rest. We use it for our data synchronization tasks.

  
* Migrate log process from Infobright to hive  
  I participate in the Infobright to Hive project and I design and carry out the ETL migration plan. I also build a small tool called diff_checksum to check the table data consistency between the migration . This project lasts about two months and we use hive as our mainly data warehouse infrastructure later.

* Hive authorization and query service enhancement  
 Hive authorization is not completely secure, and hiveserver(hive thrift service) is not stable. I manage to wrapper a thrift service called `openhive` above hive cli for hive query need. Later we open our ETL design service to our engineers, I enhance hive authorization by adding some query hook and fixing authorization bugs.
 
* Query center Service building  
 Our query center service is the entrance of all queries, including report/api/client. It distributes the query to backend db server(mysql/hive) and caches the query result. I implement the asynchronous query part of the service.
 
<!--
* upgrade hive version in production 
-->


## Awards
* 10/2009 **Gold Medal** , 34th ACM International Collegiate Programming Contest, Asia, Shanghai
* 02/2010 **Honorable Mention** , 34th ACM International Collegiate Programming Contest **World Finals**
* 10/2010 **Gold Medal** , 35th ACM International Collegiate Programming Contest, Asia, Hangzhou


## Education
Software Engineering, B.E.  
Fall 2007 - July 2011  
Fuzhou University, Fujian, China


   

