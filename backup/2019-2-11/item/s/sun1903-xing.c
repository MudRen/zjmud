// ITEM Made by player(����:sun1903) /data/item/s/sun1903-xing.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  8 23:14:49 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m����[2;37;0m", ({ "xing" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m�쾧[2;37;0m���ƶ��ɵ�һ������
[1;36m�羵��Ľ�������ɭɭƮ�����ɺ��⣬�����м�������һ�㺮��·�ͣ��������[1;31mҪ��Ϊ�����˵�ج��[2;37;0m
�����Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 6100000);
	set("point", 660);
	set("material", "silk");
	set("wield_msg", "[1;37m$N������$n[1;37m�γ���֮ʱ������ɲ��֮�䣬�ƺ��������������ڱ�����أ�һ������ɲ��֮���ƺ��������ô������[2;37;0m\n");
	set("unwield_msg", "[1;34m��Ѫ��һ��һ�����Ž��л��䣬Ⱦ�������أ�ֱ���������ǵ���ɫ����Ӱ�Ű�$n[1;34m����������뽣��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
