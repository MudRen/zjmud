#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}
void create()
{
	set_name(YEL"�������"NOR, ({"tishen kuilei"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("base_value", 10000);
		set("yuanbao", 100);
            set("no_put",1);
            set("no_get",1);
            set("no_give",1);
  		set("no_drop",1);
  		set("no_sell",1);
  		set("no_steal",1);
		set("unit", "��");
		set("base_unit", "��");
		set("weight", 10);
		set("base_weight", 10);
		set("long","���Ƕ���һ�����Ƶ�������ܣ�������ȥһ��������ʧ��\n");
	}
	setup();
}
