// chouyin.c

inherit ITEM;

void create()
{
	set_name("��ӡ", ({ "chou yin", "yin" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "�����Ƴɵ�ӡ�£�ϡ��������\n");
		set("value", 1);
		set("material", "silk");
	}
	setup();
}
