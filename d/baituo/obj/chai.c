// chai.c

inherit ITEM;

void create()
{
	set_name( "ľ��", ({ "mu chai"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ľ��\n");
		set("value", 0);
		set("material", "wood");
	}
}

int fire(object me, object ob)
{
	object fire;

	if (environment()->query_temp("warm") >= 40)
		return notify_fail("�����Ѿ����ȵ��ˣ��㻹�ǻ����ط����ɡ�\n");

	message_vision("$N��" + ob->name() + "��ȼ��" + name() +
		       "��һƬ���Ļ��ӳ�������ܡ�\n", me);

	fire = new("/clone/misc/needfire");
	fire->move(environment(me));

	destruct(this_object());
	return 1;
}
