#include <ansi.h>
#include <armor.h>

inherit "/clone/weapon/bow";

void create()
{
	set_name(HIY "���������" NOR, ({ "panlong gong", "gong", "bow" }));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("icon","05054");
		set("value", 200000);
		set("no_sell", "�ⶫ����ô����ȥ�������̵ģ�");
		set("power", 250000);   // ��������
		set("accuracy", 180);   // ׼ȷ��150%
	}
	setup();
}

