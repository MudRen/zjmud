// ITEM Made by player(������:uiop) /data/item/u/uiop-plftj.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan 28 11:33:03 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m�������콣[2;37;0m", ({ "plftj" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
[1;36m����������Խ���õľ������������ʮ������ߡ�������Ϊ��Ϊ�������ͣ�����ʻ��������ֳƷ��챦������ʹ���ߵ�Ҫ�󼫸ߡ�[2;37;0m
�����Ͽ���һ��С�֣�������(uiop)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "[31m$N�����������壬������������̳�����壬������Խ�����飬����̳ǰ�����������������շ�������Խ��������룬���ұ���ɨ��ƽ����[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
