// chanhs.c ����˿

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "����˿" NOR, ({"silk", "chan hunsi", "si"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����Ө͸����ϸ˿��������˿�Ͳ�˿���֯�Ͷ��ɵġ�\n");
		set("unit", "��");
		set("value", 10000);
		set("item_origin", 1);
		set("material_attrib", "silk");
		set("material_name", WHT "����˿" NOR);
		set("can_make", ({ "��", "����", "ս��", "ѥ��", "����" }));
		set("power_point", 35);
	}
}
int query_autoload() { return 1; }