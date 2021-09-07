// shuzhi.c

#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
	set_name(GRN"����֦"NOR, ({ "shu zhi"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
	set("long", "����һ����ɽ�õ���֦��\n");
	set("value", 50);
		set("material", "wood");
		set("wield_msg", "$N�ó�һ��$n���������С�\n");
		set("unwield_msg", "$N�������е�$n��\n");
	}

	init_staff(5);
	setup();
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
