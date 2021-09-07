// jinsha.c

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
	set_name(HIR "������[��Ʒ]" NOR, ({ "chongmai dan3" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������������澭�����ĵ��ߡ�\n");
		set("base_unit", "��");
		set("base_value", 500);
		set("yuanbao", 30);
		set("needle/level",15);
		set("base_weight", 1);
	}
	setup();
}

