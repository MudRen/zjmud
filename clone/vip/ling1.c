inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"ͨ������"NOR, ({"tongxing ling1"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 1);
  set("no_give",1);
  set("no_drop",1);
  set("no_sell",1);
  set("no_steal",1);
		set("unit", "��");
		set("long","���Ƕ���һ�巢�ŵ�ͨ�����ƣ������͵�ŵ�Ϳռ�ʱ���������ó���\n");
	}
}

int query_autoload() { return 1; }