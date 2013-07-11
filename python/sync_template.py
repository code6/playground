#coding=utf8

from jinja2 import Template

sync_template = '''

{%macro trim_input(name) -%}
    {{ name | trim }}
{%- endmacro %}

##Description##
{{ description }}

##TaskInfo##
creator = '{{ creator}} @meituan.com'
tasktype = 'sync'

{% if hive_deltamerge_keys %}
deltamerge = True
{% endif %}

stream = {
    {% if hive_deltamerge_keys %}
    'unique_keys' : '{{ trim_input(hive_deltamerge_keys) }}',
    {% endif %}
}

source  = {
        'db' : META['{{  trim_input(source) }}'],
        'table' : '{{ trim_input(table) }}'
}

target = {
        'db' : META['{{ target | trim }}'],
        'table' : '{{ targettable if targettable else table | trim }}'
}

{% if where %}
##SQL.Where##
{{ trim_input(where) }}
{% endif %}

{% if limit %}
##SQL.Limit##
{{ trim_input(limit) }}
{% endif %}


'''

d = {
'source': 'dim    ',
'table' : 'deal',
'target': 'stat',
#'targettable':'deal_stat'
'where' : ' datekey >= $now.datekey ',
'limit' : '1',
'hive_deltamerge_keys' : '   id_1, id2    ',
    }


tpl = Template(sync_template)
print tpl.render(d)
