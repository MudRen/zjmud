// ITEM Made by player(��������:awsl) /data/item/a/awsl-ndr.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 30 11:07:02 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m�浶��[2;37;0m", ({ "ndr" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
[1;31m����������������ɱ�˵ļ�����������ʲô����ȥ���Σ��⣬ʼ��������ʵ[2;37;0m
�����Ͽ���һ��С�֣���������(awsl)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "�γ�������������[2;37;0m\n");
	set("unwield_msg", "�Ż�ȥ������������[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
