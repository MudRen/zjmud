// ITEM Made by player(������:uiop) /data/item/u/uiop-hsp.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 10:47:04 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31m�����ʥ��[2;37;0m", ({ "hsp" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
[31m����һ�����ս�ۣ�����ԼԼ���Կ�������Ϊһ���Ƕ���[2;37;0m
ս��Ե�Ͽ���һ��С�֣�������(uiop)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[31m$N������������ӦǬ����ȼ������͸���ţ����������ǲ����������Ƕ����ֳ�������ӧǹ��ͨ����ع��񾪣������µؼ���������캢�����١���[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[2;37;0m[31m�����ʥ��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
