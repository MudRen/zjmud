// ITEM Made by player(����:q456789) /data/item/q/q456789-gui.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 16:42:56 2019
#include <ansi.h>
#include <weapon.h>

inherit AXE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m�¶���[2;37;0m", ({ "gui" }));
	set_weight(9900);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m����[2;37;0m���ƶ��ɵ�һ�Ѹ���
�����Ͽ���һ��С�֣�����(q456789)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wield_msg", "[1;36m$N[1;36mһ����Х������һ��[1;36m$n[1;36m��[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_axe(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
