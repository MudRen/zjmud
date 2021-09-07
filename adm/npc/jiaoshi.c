// jiaoshi.c ��ʿ

#include <ansi.h>

#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR	"/data/item/ring/"

inherit NPC;

void create()
{
	set_name("���󴫽�ʿ", ({ "jiao shi", "jiaoshi", "marriage witness" }));
	set("long", 
		"������һ��ĺ�ɫ���Σ���ɫ���¡�\n");
	set("gender", "����");
	set("age", 35);
	set("combat_exp", 1000);
       set("icon","01047");
	set("inquiry", ([
		"���": "Ҫ������𣿴�Ҷ����ϵ۵���Ů���ҿ���Ϊ����֤�顣",
		"���": "��Ȼ������˸е�ʹ�࣬����Ҳ�����һ�������ʹ�࣡",
	]));

	setup();
	seteuid(getuid());
}

int do_witness(object me, object ob)
{
	message_vision("$N��������������$n������������ˮ���������òŶ�" +
		       name() + "������λ���������ǵ�֤���˰ɣ�\n\n",
		       me, ob);

	if (! living(ob))
	{
		message_vision(name() + "Ŀ�ɿڴ��˰��Ŷ�$N������"
			       "���㻹���Ȱ���λŪ����˵�ɡ�\n", me);
		return 1;
	}

	if (! userp(ob))
	{
		message_vision(name() + "�������ǿ�Ц��Цɶ"
			       "�أ���Ҳ�Ǻǵĸ���ɵЦ��\n", me);
		return 1;
	}

	message_vision(name() + "���ͷ�������ܺã��ܺã���Ҷ���"
		       "�ϵ۵���Ů�����û�����⡣���������Ƕ���������Ը�𣿡�\n"
		       "˵��ת��ͷ������$n�ʵ�������Ը���" +
		       (me->query("gender") == "Ů��" ? "��" : "��") +
		       "��Ϊ������(right/refuse)����\n", me, ob);

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

	message_vision("$N���˿�$n����ͷ��������Ը�⣡��\n", me, ob);
	command("chat �ܺã�������������" + me->name(1) + "��" + ob->name(1) +
		"�Ѿ���Ϊ�Ϸ��ķ����ˣ�");
	message("visoin", name() + "Ц�ŶԶ���˵������Խ��"
		"��ָ�͸����ǣ��������ҵ�����ɣ���\n\n", environment(me));

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
		       name() + "���εĶ�$n������һ����Ը�ǲ��еģ�"
		       "���Ƿ���...�㻹�����˰ɡ���\n", me, ob);
	return 1;
}

int do_divorce(object me)
{
	object ob;

	if (me->query("couple/witness") != name())
	{
		message_vision(name() + "ҡҡͷ����$N��������"
			       "�������ǵ�֤���ˣ�������鲻Ҫ���ң���\n", me);
		return 1;
	}

	ob = find_player(me->query("couple/id"));
	if (! ob || environment(ob) != environment(me))
	{
		message_vision(name() + "�Ծ��Ŀ���$N��������ô��Ҫ��飿"
			       "����Ҫ������ôҲ�ð��˼�����������\n", me);
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
		message_vision(name() + "̾�˿�������ͷ���˿�$n���ʵ�������"
			       "����Ҫ��" + ob->name() + "����𣿡�\n\n", me, ob);
		tell_object(ob, YEL + name() + "���ĵĸ����㣺Ҫ���������������("
				"divorce " + me->query("id") + ")��ʾ�����Ѷ���\n");
		me->set_temp("pending/submit_divorce", 1);
		return 1;
	}

	message_vision(name() + "�����Ķ�$N��$n��������Ȼ����˫��"
		       "�Ѿ���Ը����һ���ˣ��Ǿͷֿ��ɣ���\n\n", me, ob);
	command("chat �ӽ�����" + me->name(1) + "��" + ob->name(1) +
		"�����Ƿ����ˣ������Ժ�û��ʲô��ϵ�ˣ�");
	UPDATE_D->clear_user_data(me->query("id"), "couple");
	return 1;
}

int accept_fight()
{
	command("shake");
	command("say �����й����Ǵ�����ģ����������Ȥ���������ǵĴ���ʿ��");
	return notify_fail("�㻹�����˰ɣ�\n");
}

int accept_hit()
{
	command("fear");
	command("say ����ô�������ˣ�");
	return notify_fail("�㻹�����˰ɣ�\n");
}

int accept_kill()
{
	command("say �й��˺�Ұ����������ô��������");
	return 1;
}

void unconcious()
{
	die();
}

void die()
{
	command("chat �й�����Ұ�����������ˡ�");
	message_vision("$N��æ�����ˡ�\n", this_object());
	destruct(this_object());
}
