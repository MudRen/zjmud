// ITEM Made by player(����:sun1903) /data/item/s/sun1903-sun.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 02:00:26 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m�λ�[2;37;0m", ({ "sun" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m����˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
[1;37m����������Ҷ���Ƶ�ѩ�׹��ߣ��۷�ѩ�ף�һ����Ⱦ�����չⶼ������˼���°߲�����Ӱ[2;37;0m
ս��Ե�Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "silk");
	set("wear_msg", "$N����һ�룬һ���Ӱ���������$n�����ĸ�������[2;37;0m\n");
	set("remove_msg", "$N����һ�ӣ�$n��ʧ������������ϧ����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
