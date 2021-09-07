// fish.h

int is_fish() { return 1; }

int has_died = 0;

void setup()
{
	set_weight(500 + random(1000));
	set("value", query_weight() / 50);

	::setup();
	if (clonep())
		call_out("die", 60 + random(60));
}

void die()
{
	remove_call_out("die");

	if (! environment())
	{
		destruct(this_object());
		return;
	}

	message("vision", name() + "���������ӣ����ˡ�\n", environment());
	set("long", "����һֻ" + name() + "�����Ѿ����ˡ�\n");
	set_name("��" + name(), ({ "si xia", "sixia" }));
	has_died = 1;
	call_out("decay", 30 + random(30));
	set("value", query("value") / 2);
}

void decay()
{
	remove_call_out("decay");

	if (! environment())
	{
		destruct(this_object());
		return;
	}

	message("vision", name() + "�����ˣ�����һ�����ζ��\n", environment());
	set("long", "����һֻ" + name() + "�����Ѿ���ʼ�����ˡ�\n");
	set_name("��Ϻ", ({ "lan xia", "lanxa" }));
	set("value", 0);
	call_out("vanish", 20 + random(20));
}

void vanish()
{
	if (environment())
	{
		message("vision", "һ��紵������" + name() + "����ɢ�ˡ�\n", environment());
	}

	destruct(this_object());
}

void sold()
{
	destruct(this_object());
}

int broil(object me, object ob)
{
	object fob;

	if (query("value") == 0)
	{
		write("��ôһ����Ϻ����ʲô��\n");
		return 1;
	}

	me = this_player();
	if (me->is_busy())
	{
		write("������æ���أ�������ٿ��ɡ�\n");
		return 1;
	}

	message_vision("$N��" + name() + "����" + ob->name() +
		       "��ϸϸ�Ŀ��ţ�ֻ����ࣱ�ࣵ�������" + name() +
		       "�����ı���˺�ɫ��ɢ�����������˵���ζ��\n", me);

	write(HIY "���Ϻ�����ˣ�"NOR"\n");
	fob = new("/clone/food/xia");
	fob->move(me, 1);
	destruct(this_object());
	me->start_busy(1);
	return 1;
}
