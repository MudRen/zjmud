// bone.c �˹�

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
	set_name(WHT "�˹�" NOR, ({ "bone", "gu" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 0);
		set("material", "bone");
		set("long", "����һ����ɭɭ���˹�ͷ��\n");
		set("wield_msg", "$N���һ��$n�������С�\n");
		set("unequip_msg", "$N�����е�$n������䡣\n");
	}
	init_staff(1);
	setup();
}
