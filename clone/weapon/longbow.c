// longbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
	set_name("���¹�", ({ "yinyue bow", "bow", "yinyue", "gong" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("icon","05053");
		set("long", "һ�ų������������Ϊ���£������൱�õ�׼ȷ�ȡ�\n");
		set("value", 80000);
		set("power", 180000);   // ��������
		set("accuracy", 150);   // ׼ȷ��150%
	}
	setup();
}
