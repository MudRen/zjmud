// wujins.c �ڽ�˿

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "�ڽ�˿" NOR, ({ "black silk", "wujin si", "si"}));
	set_weight(1800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���ڰ�����ϸ˿�������ڽ�˿�Ͳ�˿���֯�Ͷ��ɡ�\n");
		set("unit", "��");
		set("value", 20000);
		set("item_origin", 1);
		set("material_attrib", "silk");
		set("material_name", YEL "�ڽ�˿" NOR);
		set("can_make", ({ "��", "����", "ս��", "����", "����", "ѥ��" }));
		set("power_point", 70);
	}
}
int query_autoload() { return 1; }