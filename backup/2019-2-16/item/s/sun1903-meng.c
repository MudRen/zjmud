// ITEM Made by player(����:sun1903) /data/item/s/sun1903-meng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 21:34:30 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m����[2;37;0m", ({ "meng" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
�����Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "[1;31mԶ�ŵ�һ����������ɫ�ڰ׽��ʵ�һ˲�䣬һ˫�ֻ�������˫�ֺ���֮����һ�ؽ�����ֻ�н���������������[2;37;0m\n");
	set("unwield_msg", "[1;33m$Nֱ�����Ҳ������֣����ղ����Լ��Ľ���[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
