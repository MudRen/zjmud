// shoutao.c

#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
	set_name( "��ָ��", ({ "zhitao", "zhi tao" }) );
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������������������ָ�ף�ǰ�˷������У��ȿɰ����������ˣ��ֿɱ���ָ�ؽڡ�\n");
		set("value", 6000);
		set("material", "iron");
		set("armor_prop/armor", 5);
		set("armor_prop/finger", 5);
	      set("armor_prop/unarmed_damage", 20);
	}
	setup();
}
