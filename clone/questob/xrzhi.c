// xrzhi.c

inherit ITEM;

void create()
{
	set_name("����ָ", ({ "xianren zhi", "zhi" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "����ȥ��ͬ������ָһ�㣬��ȴ��δ���˼ӹ���ĥ����Ȼ��ʯ��\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
