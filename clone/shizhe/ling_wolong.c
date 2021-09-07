
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
	set_name(HIC "������" NOR, ({ "wolong ling" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һöʽ�����ӵ�������������һ����ͼ�����Ǳ������������һ��ׯ԰����֪��ʲô���⡣\n");
		set("base_unit", "��");
		set("base_value", 500000);
		set("yuanbao", 2000);
		set("base_weight", 1);
	}
	setup();
}

