#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(RED "��ľ����" NOR, ({ "shelf"}) );
	set_weight(50000);
	set_max_encumbrance(800000);
	set("no_get", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("prep", "in");
		set("unit", "ֻ");
		set("long", RED "һֻ�������ľ���ƣ���������佣�ļ��ӡ�"NOR"\n");
		set("value", 1);
	}
}

int is_container() { return 1; }

