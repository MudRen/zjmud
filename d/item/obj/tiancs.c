// tiancs.c ����˿

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW "����˿" NOR, ({ "white silk", "bingcan si", "si"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����Ө��͸��ϸ˿����Ȼ�����׹⡣\n");
		set("unit", "��");
		set("value", 100000);
		set("item_origin", 1);
		set("material_attrib", "silk");
		set("material_name", HIW "����˿" NOR);
		set("can_make", ({ "��", "����", "ս��", "����", "����", "ѥ��" }));
		set("power_point", 100);
	}
}
int query_autoload() { return 1; }
