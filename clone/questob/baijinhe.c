// baijinhe.c

inherit ITEM;

void create()
{
	set_name("�׽��", ({ "baijin he", "he" }));
	set_weight(1800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һ�������Ľ����������������������Ҫ��һЩ��\n");
		set("value", 2000);
		set("material", "platina");
	}
	setup();
}
