//lingfeixue.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("���ѩ", ({ "ling feixue", "feixue", "ling" }) );
	set("gender", "Ů��" );
	set("title",HIY "ǧ��һЦ" NOR);
	set("age", 23);
	set("long", 
	"���ѩԭ��һ����¥���ˣ�����������һλ��ٿ��У���˵���\nȺ��¥Ҳ����λ��Ա�������ġ�");
	set("str", 40);
	set("dex", 40);
	set("con", 40);
	set("int", 40);
	set("per", 40);
	set("shen_type", -1);
	set_skill("unarmed", 50);
	set_skill("force", 50);
	set_skill("dodge", 50);
	set("combat_exp", 25000);
	set("max_qi", 300);
	set("max_jing", 300);
	set("qi", 300);
	set("jing", 300);
	set("neili", 500);
	set("max_neili", 500);
	set("attitude", "friendly");
	set("inquiry", ([
	"name" : "�Ҿ���������һЦ��ǧ�𡱵ĳ�����һ��Ů���ѩ��",
	"here" : "������ǳ�����������������Ⱥ��¥��",
	]) );

	setup();
	set("chat_chance", 15);
	set("chat_msg", ({
		"���ѩ�����˵��������������һЦ��Ҳ��֪�ж����������ݵ�����ȹ�¡�\n",
		"���ѩ������˼�ĵ���Ҳ��֪���������ϲ��ϳ����ӿ͡�\n",
		"���ѩ����˵������λ�͹٣���������Ⱥ��¥������ˣ�����Ҫʲô���Ĺ��ﶼ�С�\n",
	}) );

	carry_object(__DIR__"obj/skirt")->wear();
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting()) 
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	if (! objectp(me) || environment(me) != environment())
		return;

	command("look " + me->query("id"));

	if (me->query("class") == "bonze")
	{
		command("say �ǣ�" + RANK_D->query_respect(me) +
			"Ҳ���������Ⱥ��¥����");
		command("say ������¥�ɣ�");
	}

	if (me->query("gender") == "Ů��")
	{
		command("say ��ѽ����λ" + RANK_D->query_respect(me) +
			"Ҳ����Ҥ�ӣ��ɺ���ͳ��");
		command("sigh");
	}
	command("say ¥�ϵĹ����ǣ��п������ˣ�");
	return ;
}

void accept_kill(object me)
{       
	object ob;
	if (is_fighting()) return;
	if (query("called")) return;
	command("say Ҫɱ���ˣ������˾�������");
	ob = present("bao biao");
	if (! ob)
	{
		seteuid(getuid());
		ob=new(__DIR__"baobiao");
		ob->move(environment());
	}
	message_vision(HIC "\n��Ȼ�����������������ڣ���$N"
		       HIC "��һ������ʲô����������£���"
		       "������\n"NOR"\n", me);
	ob->kill_ob(me);
	ob->set_leader(me);
	me->kill_ob(ob);
	set("called", 1);
	call_out("regenerate", 200);
}

int regenerate()
{
	set("called", 0);
	return 1;
}
