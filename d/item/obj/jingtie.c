// jingtie.c ��������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "��������" NOR, ({"iron", "tie"}));
	set_weight(4500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�������ľ�������ұ���ľ�����\n");
		set("unit", "��");
		set("value", 5000);
		set("item_origin", 1);
		set("material_attrib", "iron");
		set("material_name", WHT "����" NOR);
		set("can_make", "all");
		set("not_make", ({ "����", "ս��" }));
		set("power_point", 30);
	}
}
int query_autoload() { return 1; }