// xuantie.c ����ʯ

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN "����ʯ" NOR, ({"xuan tie", "tie"}));
	set_weight(30000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���������Щ����ʯͷ���������ие���Ϊ���أ�Զʤͭ����\n");
		set("spectxt", "����װ���Ĳ��ϡ�\n");
		set("unit", "��");
		set("value", 3000000);
//		set("yuanbao", 300);
        set("no_sell",1);
		set("item_origin", 1);
		set("material_attrib", "steel");
		set("material_name", CYN "����" NOR);
		set("can_make", "all");
		set("not_make", ({ "��", "ս��", "��", "����", "����" }));
		set("power_point", 70);
	}
}

int query_autoload() { return 1; }