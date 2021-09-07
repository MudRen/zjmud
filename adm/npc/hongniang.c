// hongniang.c ����

#include <ansi.h>

#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR	"/data/item/ring/"

inherit NPC;

void create()
{
	set_name("����", ({ "hong niang", "hongniang", "marriage witness" }));
	set("long", 
		"����һ�����úܺÿ���С���������"
		"���Ĵ��۾�͸��һ˿���\n");
	set("gender", "Ů��");
	set("age", 18);
	set("combat_exp", 1000);
	set("max_qi",99999999);
	set("max_jing",99999999);

	set_skill("strike", 1000);
	set_skill("rulai-shenzhang", 1000);

	map_skill("strike", "rulai-shenzhang");

	prepare_skill("strike", "rulai-shenzhang");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wofo" :),
	}));

	set_temp("apply/attack", 1000);
	set_temp("apply/defense", 1000);
	set_temp("apply/damage", 1000);
	set_temp("apply/unarmed_damage", 1000);
	set_temp("apply/armor", 20000);

	set("inquiry", ([
		"���": "Ҫ��飿�ҿ���Ϊ������ý���������˶�������ô��",
		"���": "������ң������Ҳ��æ��������������Ŷ��һ�շ��ް��ն��",
	]));

	setup();
	seteuid(getuid());
}

int do_witness(object me, object ob)
{
	message_vision("$N��������������$n������������ˮ���������òŶ�" +
		       name() + "������λС�����ܷ�Ϊ����֤�飿\n\n",
		       me, ob);

	if (! living(ob))
	{
		message_vision(name() + "�ԳԵ������Ц����$N������"
			       "���㻹���Ȱ���λŪ����˵�ɡ�\n", me);
		return 1;
	}

	if (! userp(ob))
	{
		message_vision(name() + "�������ǿ�Ц��Цɶ"
			       "�أ���Ҳ�Ǻǵĸ���ɵЦ��\n", me);
		return 1;
	}

	message_vision(name() + "�������������ܺð����õúܣ���"
		       "��˵��������ԸΪ�������ڵ�Ը������֦����\n" +
		       "�ٳ���Ե���������£���" + name() + "��Ը���ˣ���������λ" +
		       RANK_D->query_respect(ob) + "ҲԸ���𣿡�\n\n", me);

	tell_object(ob, YEL + name() + "�������㣺" + me->name(1) +
			"����������أ����Ӧ(right)���ǲ���Ӧ(refuse)��"NOR"\n");
	ob->set_temp("pending/answer/" + me->query("id") + "/right",
		     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
	ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
		     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));
	me->set_temp("pending/engage", ob);
	return 1;
}

int do_right(object me, object ob)
{
	string fn;
	string fc;
	object ring;

	message_vision("$N͵͵���˿�$n��ʹ���ĵ�ͷ������Ը�⣬Ը�⼫�ˣ�\n" + name() +
		       "���ˣ�Ц����������������Ը����������ý�ˣ��ǻ����ð��𣿡�\n\n",
		       me, ob);
	command("chat ��ϲ" + me->name(1) + "��" + ob->name(1) +
		"��Ϊ����֮�ã�");
	message("visoin", name() + "Ц�ŶԶ���˵���������������"
		"��ϲ�����ӣ���û��ʲô���ֻ���͸���"
		"���������һ�Խ���ָ�ɣ���\n\n", environment(me));

	fc = read_file(MARRY_RING);
	fc = replace_string(fc, "LONG_DESCRIPTION",
			    "����" + me->name(1) + "��" +
			    ob->name(1) + "�Ľ���ָ�������˵Ķ���֮�\n");

	// give ring to me
	fn = RING_DIR + me->query("id");
	if (file_size(fn + ".c") > 0)
	{
		if (ring = find_object(fn)) destruct(ring);
		rm(fn + ".c");
	}
	assure_file(fn);
	write_file(fn + ".c", fc);
	ring = load_object(fn);
	ring->move(me, 1);
	tell_object(me, HIY "������һ������ָ��"NOR"\n");
	me->set("can_summon/" + "wedding ring", fn);

	// give ring to ob
	fn = RING_DIR + ob->query("id");
	if (file_size(fn + ".c") > 0)
	{
		if (ring = find_object(fn)) destruct(ring);
		rm(fn + ".c");
	}
	assure_file(fn);
	write_file(fn + ".c", fc);
	ring = load_object(fn);
	ring->move(ob, 1);
	tell_object(ob, HIY "������һ������ָ��"NOR"\n");
	ob->set("can_summon/" + "wedding ring", fn);
	
	// record
	me->set("couple/id", ob->query("id"));
	me->set("couple/name", ob->name(1));
	me->set("couple/witness", name());
	me->save();
	ob->set("couple/id", me->query("id"));
	ob->set("couple/name", me->name(1));
	ob->set("couple/witness", name());
	ob->save();
	return 1;
}

int do_refuse(object me, object ob)
{
	message_vision("$NƳ��$nһ�ۣ�ת��ͷȥ���ٿ���������"
		       "���ڣ����ޡ��ޡ��������ޣ���\n" +
		       name() + "���εĶ�$n��������Ҳ�����ˣ�"
		       "�׻�˵ǿŤ�Ĺϲ���...��\n", me, ob);
	return 1;
}

int do_divorce(object me)
{
	object ob;

	if (me->query("couple/witness") != name())
	{
		message_vision(name() + "ҡҡͷ����$N�������ҿ�"
			       "�������ǵ�ý�ˣ�����Ҫ����룬�������ң���\n", me);
		return 1;
	}

	ob = find_player(me->query("couple/id"));
	if (! ob || environment(ob) != environment(me))
	{
		message_vision(name() + "�Ծ��Ŀ���$N��������ô����"
			       "���ˣ��������ް��պð�������Ҫ������"
			       "ôҲ�ð��˼�����һ��̸̸������\n", me);
		return 1;
	}

	if (! living(ob))
	{
		message_vision(name() + "ҡҡͷ����$N��������˵��λ" +
			       RANK_D->query_respect(me) +
			       "����ôҲ�õ��˼��ѹ�����˵�ɣ���\n", me);
		return 1;
	}

	if (me->query_temp("pending/submit_divorce"))
	{
		message_vision(name() + "ҡҡͷ����$N����������"
			       "ʲô����Ҳ�������˼ҵ���˼����\n",
			       me);
		return 1;
	}

	if (! ob->query_temp("pending/submit_divorce"))
	{
		message_vision(name() + "����̾�˿�����һ�����ɵ�����Ҳ"
			       "������Щ��ɣ����ͷ���˿�$n���ʵ�������"
			       "Ҳ�������Ĳ���" + ob->name() + "���ˣ���\n\n", me, ob);
		tell_object(ob, YEL + name() + "���ĵĸ����㣺Ҫ���������������("
				"divorce " + me->query("id") + ")��ʾ�����Ѷ���\n");
		me->set_temp("pending/submit_divorce", 1);
		return 1;
	}

	message_vision(name() + "ʹ�ĵĶ�$N��$n������������Ϊ����"
		       "������ý��ʱ�򣬿���û�뵽������ôһ�죡��\n\n", me, ob);
	command("chat �ӽ�����" + me->name(1) + "��" + ob->name(1) +
		"�����ˣ��Ժ�ɾ͸��߸���·����");
	UPDATE_D->clear_user_data(me->query("id"), "couple");
	return 1;
}

int accept_fight()
{
	command("fear");
	command("say �������Һ����µġ�");
	return notify_fail("�㻹�����˰ɣ�\n");
}

int accept_hit()
{
	command("say ��Ҫ������Ҫ�Ҷ��֣�");
	return notify_fail("�㻹�����˰ɣ�\n");
}

int accept_kill()
{
	command("say ѽ�������ʲô��");
	return 1;
}

void unconcious()
{
	die();
}

void die()
{
	command("chat �����ˣ��������ˣ�");
	message_vision("$N��Ҳ�Ƶ������ˡ�\n", this_object());
	this_object()->set("qi",99999999);
	this_object()->set("jing",99999999);
}
