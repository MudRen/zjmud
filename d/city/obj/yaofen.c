// yaofen.c ҩ��

inherit ITEM;

void create()
{
	set_name("ҩ��", ({ "yao fen" , "yao", "fen" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ר�����˵�ҩ�ۡ�\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	write("�����һ��ҩ�ۣ������۾���Щʹ��\n");
	return 1;
}
