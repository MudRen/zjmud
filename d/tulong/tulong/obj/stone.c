#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
	set_name(WHT "��ʯͷ" NOR, ({ "stone" }) );
	set_weight(16000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		 set("icon","01021");
		set("long", "һ�����Բ������ʯͷ��\n");
		set("value", 0);
		set("material", "iron");
	}
	init_hammer(10);
	setup();
}

