// ITEM Made by player(������:uiop) /data/item/u/uiop-ftj.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 23 09:59:51 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31m�������콣[2;37;0m", ({ "ftj" }));
	set_weight(45000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[36m����[2;37;0m���ƶ��ɵ�һ������
[31m����������Խ���õľ������������ʮ������ߡ�������Ϊ��Ϊ�������ͣ�����ʻ��������ֳƷ��챦������ʹ���ߵ�Ҫ�󼫸ߡ�[2;37;0m
�����Ͽ���һ��С�֣�������(uiop)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "[31m$N�����������壬������������̳�����壬������Խ�����飬����̳ǰ�����������������շ�������Խ��������룬���ұ���ɨ��ƽ����[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
