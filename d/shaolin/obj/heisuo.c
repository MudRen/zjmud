// ����

#include <ansi.h>
#include <weapon.h>

inherit WHIP;

void create()
{
	set_name("����", ({ "black whip", "hei suo", "suo", "whip" }));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����ڵĳ��ޣ��������ۣ��������ֳ��أ���\n"
			    "��ʧ���ͣ�ʵ����ǧ������֮�\n");
		set("no_sell", "����ɶ�����գ��ϵ��õģ�\n");
		set("value", 50000);
		set("material", "steel");
		set("wield_msg", BLK "$N" BLK "һ���֣�������Ϣ�Ľ�$n�������С�"NOR"\n");
		set("unwield_msg", WHT "$N" WHT "�����е�$n�����պá�"NOR"\n");
		set("stable", 70);
	}

	init_whip(120);
	setup();
}
