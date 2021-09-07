// muding.c ľ��

#include <ansi.h>

inherit ITEM;

int do_clear(string arg);
int do_light(string arg);
int do_make(string arg);
int do_liandu(string arg);
void back_owner(object me);

mapping insects = ([
	"zhizhu"	: 100000,
	"chanchu"       : 100000,
	"xiezi"	 : 100000,
	"wugong"	: 100000,
	"duzhu"	 : 20000,
	"huoxie"	: 20000,
	"jinwugong"     : 20000,
	"heiguafu"      : 5000,
]);

void create()
{
	set_name("ľ��", ({ "mu ding", "muding", "ding" }) );
	set_weight(1000);
	set("long", @LONG
һֻľ�ƵĶ�������ɢ�������ϵ���ζ������ϸϸ�о���ȴ��һ����ζ��
LONG );
	set("unit", "ֻ");
	set("value", 2500);
	set("no_sell", 1);
	set_max_encumbrance(600);
	setup();
}

int is_container() { return 1; }

void init()
{
	add_action("do_clear", "clear");
	add_action("do_light", "light");
	add_action("do_liandu", "liandu");
	add_action("do_make", "make");
}

int do_clear(string arg)
{
	object me;
	object *ob;
	int i;
	int k;

	if (! id(arg))
		return notify_fail("��Ҫ���ʲô��\n");

	me = this_player();
	ob = all_inventory(this_object());
	if (! ob)
		return notify_fail("����" + name() + "����û���κζ�����\n");

	if (query_temp("id") != me->query("id") &&
	    query_temp("id") && environment() != me)
		return notify_fail("�˼����õ�" + name() + "����Ϲ��ʲô��\n");

	if (query_temp("lighting"))
	{
		delete_temp("lighting");
		delete_temp("id");
		remove_call_out("catch_insect");
		message_vision("$N��" + name() + "�еĻ�Ϣ���ˡ�\n", me);
	}

	k = 0;
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_insect())
			continue;

		message_vision("$N��" + name() + "�����$n���˳������ӵ��ˡ�\n",
			       me, ob[i]);
		k++;
		destruct(ob[i]);
	}

	if (! k)
		message_vision("$N���˻�" + name() + "��ûɶ���档\n", me);

	back_owner(me);
	return 1;
}

int do_light(string arg)
{
	object ob;
	object me;

	me = this_player();
	if (query_temp("id") != me->query("id") &&
	    query_temp("id") && environment() != me)
		return notify_fail("�˼����õ�" + name() + "����Ϲ��ʲô��\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("������Ҳ����������̫�ðɡ�\n");

	if (query_temp("lighting"))
		return notify_fail("����" + name() + "������ȼ�����ϡ�\n");

	if (me->is_busy())
		return notify_fail("��������æ���أ���һ����ɡ�\n");

	if (me->is_fighting())
		return notify_fail("��ܵ�ʱ���㻹����˼Ū�����\n");

	if (! objectp(ob = present("xiang liao", me)) ||
	    ! ob->query_amount())
		return notify_fail("����������û�����ϣ��޷�ʹ��" + name() + "��\n");

	ob->add_amount(-1);
	message_vision(HIM "\n$N" HIM "��" + name() + HIM "���ڵ��ϣ�����"
		       "���ϣ���ȼ�󷢳�����������"NOR"\n", me);
	set_temp("lighting", 1);
	set_temp("id", me->query("id"));

	if (environment() == me)
	{
		this_object()->move(environment(me));
		  set_temp("owerid",me->query("id"));
		set("no_get", name() + "���������������أ����Ҷ���\n");
	}

	remove_call_out("catch_insect");
	call_out("catch_insect", random(4) + 2, me);

	return 1;
}

void back_owner(object me)
{
	if (environment() != me)
	{
		this_object()->move(me);
		if (! me->is_busy())
			me->start_busy(1);
	}
}

void catch_insect(object me)
{
	object env;
	object insect, here;
	mapping rs;
	string *st;
	int i;
	int sum;

	delete_temp("lighting");
	delete_temp("id");
	delete("no_get");

	 here = environment(me);
	env = environment(this_object());
	if (! objectp(me) || environment(me) != env || ! living(me))
	{
		message_vision("����������ɢȥ�ˡ�\n", this_object());
		return;
	}

	if (! env->query("outdoors") || env->query("no_insect"))
	{
		message_vision("��������ɢȥ�ˣ�ɶҲûץ��������$N�ǰ�æ���ˡ�\n"
			       "$N̾�������ջ���" + name() + "��\n",
			       me);
		back_owner(me);
		return;
	}
	 
	rs = insects;
	if (mapp(env->query("insects")))
		rs += env->query("insects");

	st = keys(rs);
	sum = 0;
	for (i = 0; i < sizeof(st); i++)
	{
		if (! intp(rs[st[i]]))
			rs[st[i]] = 0;
		  //ӵ����ľ����
		  if (st[i] == "bingcan")
		  {
			if(query_temp("owerid") == me->query("id"))
			   rs[st[i]] = 1000;
			else
			   rs[st[i]] = 0;
			delete_temp("owerid");
		  }
		sum += rs[st[i]];
	}

	if (! sum) return;
	sum = random(sum);
	for (i = 0; i < sizeof(st); i++)
	{
		if (sum < rs[st[i]])
		{
                 if (me->query("getbingcan")) st[i]="bingcan";
		     catch(insect = new("/clone/insect/" + st[i]));
		     if (! objectp(insect)) break;
			here = environment(me);
			if (st[i] == "bingcan")
			{
				//�����������ľ����ܻ�ñ���
				if(!here || (string)file_name(here) != "/d/mingjiao/youjing")
				{
					continue;
				}
				//��lucky���츳��������10��
				if (me->query("special_skill/lucky") != 1 && random(10) != 0)
				{
					continue;
				}
			}
			message_vision(HIG "����Խ��Խϡ����ͻȻһ" +
				       insect->query("unit") + insect->name() +
				       HIG "������" + name() + HIG "��"NOR"\n", me);
			if (! insect->move(this_object()))
			{
				message_vision("��ϧ" + name() + "ʣ�µĿռ�̫С�ˣ�" + insect->name() +
					       "û�����ȥ���ߵ��ˡ�\n", me);
				destruct(insect);
				message_vision("$N̾�������ջ���" + name() + "��\n", me);
				back_owner(me);
				return;
			} else
			if (me->is_fighting() || me->is_busy())
			{
				message_vision("����$N��æ�ţ�ֻ���������Ŀ���" +
					       insect->name() + "���ߵ��ˡ�\n", me);
				destruct(insect);
				return;
			}
			insect->unconcious();
			back_owner(me);
			message_vision("$N��ϲ����æ����" + name() + "��\n", me);
                  me->delete("getbingcan");
			me->start_busy(1);
			return;
		}
		sum -= rs[st[i]];
	}

	message_vision("��������ɢȥ�ˣ�ɶҲûץ���������ǰ�æ���ˡ�\n"
		       "$N̾�������ջ���" + name() + "��\n",
		       me);
	back_owner(me);
}

int do_liandu(string arg)
{
	object me;
	object *ob;
	int i;
	int amount;

	me = this_player();

	if (me->query_skill("poison", 1) < 50)
		return notify_fail("��Ļ���������򲻹�������������\n");

	if (me->query_skill("huagong-dafa", 1) < 80)
		return notify_fail("��Ļ����󷨻�򲻹�������������\n");

	ob = all_inventory(this_object());
	if (! ob)
		return notify_fail("����" + name() + "����û���κζ�����\n");

	if (query_temp("id") != me->query("id") &&
	    query_temp("id") && environment() != me)
		return notify_fail("�˼����õ�" + name() + "����Ϲ��ʲô��\n");

	if (query_temp("lighting"))
		return notify_fail("����" + name() + "������ȼ�������ء�\n");

	for (amount = 0, i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_insect()) continue;
		amount++;
	}

	if (! amount) return notify_fail(name() + "��ûɶ���棬����ʲô����\n");

	message_vision(HIG "$N" HIG "�������£���������" + name() +
		       HIG "��ڤ��������"NOR"\n", me);

	amount = 0;
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_insect()) continue;
		switch (ob[i]->absorbed(me))
		{
		case 1:
			break;

		case -1:
			return 1;

		default:
			message_vision(HIM "$n" HIM "����������ˮ�����뵽$N"
				       HIM "���ġ�"NOR"\n",
				       me, ob[i]);
			break;
		}

		amount += (int)ob[i]->query("insect_poison/level") *
			  (int)ob[i]->query("insect_poison/maximum");
		destruct(ob[i]);
	}

	if (! me->is_busy())
		me->start_busy(random(3));

	message_vision("\n$N������ϣ������۾���վ��������\n", me);
	amount /= 4;
	if (amount < 5)
	{
		tell_object(me, "�����û���κ�Ч����\n");
		return 1;
	}

	if (me->can_improve_skill("poison"))
		me->improve_skill("poison", 1 + random(amount / 3));

	if (me->can_improve_skill("huagong-dafa"))
		me->improve_skill("huagong-dafa", 1 + random(amount / 3));
	tell_object(me, "�������Ļ����󷨺Ͷ����������µĽ�����\n");

	return 1;
}

int do_make(string arg)
{
	object me;
	object *ob;
	object du;
	int flvl;
	int plvl;
	int i;
	int amount;

	if (! arg)
		return notify_fail("��������" + name() + "����ʲô�����ı��ɣ�\n");

	if (arg != "poison" && arg != "du")
		return notify_fail("ʹ��" + name() + "�޷��������ֶ�����\n");

	me = this_player();

	if (me->is_busy())
		return notify_fail("������æ���ء�\n");

	if (me->query_skill("poison", 1) < 50)
		return notify_fail("��Ļ���������򲻹��������ƶ���\n");

	if (me->query_skill("huagong-dafa", 1) < 80)
		return notify_fail("��Ļ����󷨻�򲻹��������ƶ���\n");

	ob = all_inventory(this_object());
	if (! ob)
		return notify_fail("����" + name() + "����û���κζ�����\n");

	if (query_temp("id") != me->query("id") &&
	    query_temp("id") && environment() != me)
		return notify_fail("�˼����õ�" + name() + "����Ϲ��ʲô��\n");

	if (query_temp("lighting"))
		return notify_fail("����" + name() + "������ȼ�������ء�\n");

	for (amount = 0, i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_insect()) continue;
		amount++;
	}

	if (! amount) return notify_fail(name() + "��ûɶ���棬����ô�ƶ���\n");

	message_vision(HIG "$N" HIG "˫��Χס" + name() +
		       HIG "�������ڹ���ʼ�ƶ���"NOR"\n", me);

	amount = 0;
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_insect()) continue;
		message_vision(HIM "$n" HIM "����������ˮ..."NOR"\n",
			       me, ob[i]);
		amount += (int)ob[i]->query("insect_poison/level") *
			  (int)ob[i]->query("insect_poison/maximum");
		destruct(ob[i]);
	}

	me->start_busy(random(3));
	message_vision("\n$N�˹���ϣ��ɿ�����\n", me);

	// calculate poison level & duratiin
	du = new("/clone/misc/duwan");
	flvl = me->query_skill("force");
	plvl = me->query_skill("poison", 1);
	amount += plvl * 3;
	plvl = flvl * 2 / 3 + random((flvl * 2 / 3 + plvl * 2) / 3);
	amount = (amount + plvl / 2) / plvl;
	if (amount < 5)
	{
		tell_object(me, "�㷢��ʲô��û��Ū���������������ʧ���ˡ�\n");
		return 1;
	}

	if (plvl > flvl * 13 / 10)
		plvl = flvl * 13 / 10;

	du->set("poison/name", "�綾");
	du->set("poison/level", plvl);
	du->set("poison/id", me->query("id"));
	du->set("poison/duration", amount);
	du->move(this_object());

	tell_object(me, "��ҿ�" + name() + "��һ������ɫ�Ķ����Ȼ���С�\n");

	return 1;
}
