// crossbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
	set_name("��", ({ "cross bow", "bow", "nu" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("icon","05055");
		set("unit", "��");
		set("long", "һ���󣬴���ü�Ϊ���£����м��õ�׼ȷ�ȡ�\n");
		set("value", 250000);
		set("power", 250000);   // ��������
		set("accuracy", 180);   // ׼ȷ��150%
	}
	setup();
}
