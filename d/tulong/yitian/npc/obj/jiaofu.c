#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(MAG"��˹���̷̽�"NOR, ({ "bosi cloth","cloth"}) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����˹�����ܶ�Ľ̷���\n");
		set("value", 300);
		set("material", "silk");
		set("armor_prop/armor", 2);
	}
	setup();
}

