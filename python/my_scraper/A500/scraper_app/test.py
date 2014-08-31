from requests import Session

session = Session()

# HEAD requests ask for *just* the headers, which is all you need to grab the
# session cookie
#session.get('http://odds.500.com')

response = session.get(
    #url='http://odds.500.com/fenxi1/inc/yazhiajax.php/',
    url='http://odds.500.com/fenxi1/inc/yazhiajax.php?fid=454359&id=671&t=1409513727946&r=1',
    headers={
        'X-Requested-With': 'XMLHttpRequest',
    }
)

print response.text

