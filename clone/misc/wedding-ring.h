// wedding-ring.h 

#include <ansi.h>
#include <armor.h>
#include <command.h>

inherit FINGER;
inherit F_NOCLONE;
inherit F_OBSAVE;

string do_wear();
void set_attrib();

void create()
{
	set_name(HIG "����ָ" NOR, ({ "wedding ring", "ring" }) );
	set_weight(100);
	set("material", "gold");
	set("unit", "ֻ");
	set("value", 50000);
	set("no_sell", "����ҲҪ������������Լ����ˣ�");
	set("armor_prop/armor", 20);
	set("armor_prop/unarmed", 5);
	set("armor_prop/hand", 5);
	set("armor_prop/strike", 5);
	set("armor_prop/claw", 5);
	set("armor_prop/cuff", 5);
	set("armor_prop/unarmed_damage", 8);
	set("wear_msg", (: do_wear :));
	set("remove_msg", HIG "$N" HIG "��$n" HIG "����������\n" );
	if (! check_clone()) return 0;

	set("stable", 0);

	setup();
	::restore();
	set_attrib();
}

void set_attrib()
{
	int per;
	int lvl;
	int tname;
	string desc;

	// �������ò��Ӱ��
	lvl = query("enchase/lvl");
	per = query("enchase/point") * lvl / 10000;
	set("armor_prop/per", per);

	// ��������
	tname = query("enchase/name");
	desc = query("long");
	if (stringp(tname))
	{
		if (lvl >= 300)
		{
			desc += HIG "������Ƕ��" + tname + HIG
				"���ɶ��칤���������Ѱ������" + name() +
				HIG "Խ���Եþ��¡�"NOR"\n";
		} else
		if (lvl >= 200)
		{
			desc += HIG "������Ƕ��" + tname + HIG
				"������û��覴ã���ν�˼亱������Ʒ��"NOR"\n";
		} else
		{
			desc += HIG "������Ƕ��" + tname + HIG
				"�����г�" + name() + HIG +
				"�Ĳ��ף�ֻ����Щ��覴��Ե����в��㡣"NOR"\n";
		}
		set("long", desc);
	}
}

string do_wear()
{
	object me;
	string msg;
	string tname;
	int point;

	me = this_player();
	tname = query("enchase/name");
	point = query("enchase/point");

	if (me->query("gender") == "Ů��")
	{
		msg = HIG "$N" HIG "�����ɵĴ�����һ��$n"
		      HIG "���ȻһЦ��ӳ�ı������䣬ֱ��û���Ҳ���ˡ�"NOR"\n";
		if (stringp(tname))
		{
			if (point >= 150)
				msg += HIG "ֻ��" + tname + HIG "����"
				       "һ����â��ӳ���$N" HIG "����"
				       "�����䷲�������ĳ���ҡ��"NOR"\n";
			else
			if (point >= 100)
				msg += HIG "ֻ��" + tname + HIG "����"
				       "���⣬���е�$N" HIG "˵������"
				       "���ġ�"NOR"\n";
			else
				msg += HIG "ֻ��" + tname + HIG "����"
				       "һ�£�������$N" HIG "���������"
				       "��"NOR"\n";
		}
	} else
	{
		msg = HIG "$N" HIG "������һ��$n"
		      HIG "�����������緢���������㡣"NOR"\n";
		if (stringp(tname))
		{
			if (point >= 150)
				msg += HIG "ֻ��" + tname + HIG "����"
				       "һ����â��ӳ���$N" HIG "��ͬ"
				       "������������Ŀ�ɿڴ���"NOR"\n";
			else
			if (point >= 100)
				msg += HIG "ֻ��" + tname + HIG "����"
				       "���⣬��$N" HIG "Խ���Ե�ͦ��"
				       "������"NOR"\n";
			else
				msg += HIG "ֻ��" + tname + HIG "����"
				       "һ�£�������$N" HIG "�����ӡ�"NOR"\n";
		}
	}
	return msg;
}

int receive_summon(object me)
{
	object env;
	object temp;

	if ((env = environment()) && env == me)
	{
		write(name() + "����������������ٻ���ʲô����\n");
		return 1;
	}

	if (env == environment(me))
	{
		message_vision(HIG "ֻ�����ϵ�" + name() +
			       HIG "����һ����â����Ծ��$N" HIW
			       "�����У�"NOR"\n", me);
	} else
	{
		if (env)
		{
			if (env->is_character() && environment(env))
					env = environment(env);

			message("vision", HIG "ͻȻ" + name() + HIG "����һ��"
				HIG "��â��ʧ�ˣ�"NOR"\n", env);

			if (interactive(env = environment()))
			{
				tell_object(env, HIM + name() +
						 HIM "��Ȼ�����ȥ�ˣ�"NOR"\n");
			}
		}

		message_vision(HIG "һ����â������ֻ��$N"
			       HIG "���ж���һ��$n" HIG "��"NOR"\n",
			       me, this_object());
	}

	move(me, 1);
	if (environment() != me)
		return 1;

	temp = me->query_temp("armor/" + query("armor_type"));
	if (temp) temp->unequip();
	WEAR_CMD->do_wear(me, this_object());

	return 1;
}

// ��Ƕ
int do_enchase(object me, object tessera)
{
	object item;
	int lvl;

	item = this_object();
	if (stringp(item->query("enchase/name")))
		return notify_fail("����" + item->name() + "����"
				   "�Ѿ���Ƕ����Ʒ�ˡ�\n");

	if (tessera->query_wight() > 100)
		return notify_fail("�����ƷҲ̫���ˣ�����ô��Ƕ��ȥ����\n");

	if (query("equipped"))
		return notify_fail("���������������أ���ô��Ƕ�أ����������ɡ�\n");

	if (! tessera->query("can_be_enchased"))
		return notify_fail("�찡���㻹û�������հ�" +
				   tessera->name() + "��Ƕ��ȥ��\n");

	if ((lvl = me->query_skill("certosina", 1)) < 100)
		return notify_fail("�����Ƕ�����������޷���"
				   "����ô��ϸ�����\n");

	message_vision("ֻ����������һ����$N�Ѿ���" + tessera->name() +
		       "���پٵ���Ƕ����$n���档\n", me, item);
	if (lvl >= 300)
		message_vision("һʱ�䣬��ֻ����$N������������"
			       "�ޱȣ�ʵ�����˼���Ʒ��û�а��覴á�\n", item);
	else
	if (lvl >= 200)
		message_vision("ֻ��$N�������䣬���Խ����������"
			       "��û�а��ȱ����\n", item);
	else
		message_vision("ֻ��$N��ʱƽ������ɫ����Ȼ��"
			       "ЩССȱ����Ҳ��覲���褡�\n", item);
	set("enchase/name", tessera->name());
	set("enchase/point", tessera->query("magic/power"));
	set("enchase/lvl", lvl);
	save();
	destruct(tessera);
	set_attrib();

	return 1;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
	mapping data;
	object  user;

	data = ([ "enchase" : query("enchase") ]);

	if (! objectp(user = environment()))
		data += ([ "user" : query("user") ]);
	else
	if (playerp(user))
		data += ([ "user" : user->name(1) + "(" + user->query("id") + ")" ]);

	return data;
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
	if (! mapp(data))
		return 0;

	if (mapp(data["enchase"]))
		set("enchase", data["enchase"]);

	if (stringp(data["user"]))
		set("user", data["user"]);

	return 1;
}

int query_autoload() { return 1; }
