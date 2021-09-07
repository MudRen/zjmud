// caoyao.c

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
	set_name(HIG "��֪����ҩ" NOR, ({"cao yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�������������еĲ�֪���Ĳ�ҩ��һ���˶������ϳ��Ӳݡ�\n");
		set("base_unit", "��");
		set("base_weight", 1);
	}
	setup();
}
