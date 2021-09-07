// kurong.c

// ����ʱ�����six-bookû�������������һ����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define BOOK	    "/clone/book/six_book"

int ask_me();
void start_fight(object me);
void close_exit();
void open_exit();

string* names = ({
	"ben yin",
	"ben can",
	"ben chen",
	"ben guan",
	"ben xiang",
});

void create()
{
	set_name("���ٴ�ʦ", ({ "ku rong", "ku"}) );
	set("gender", "����" );
	set("title", "�����µ�ʮ����ɮ��");
	set("class", "bonze");
	set("long", @LONG
������ڶ�������������ò��
LONG );
	set("age", 95);
	set("shen_type", 1);
	set("str", 32);
	set("int", 34);
	set("con", 31);
	set("dex", 32);

	set("qi", 5500);
	set("max_qi", 5500);
	set("jing", 2700);
	set("max_jing", 2700);
	set("neili", 6700);
	set("max_neili", 6700);
	set("jiali", 60);
	set("combat_exp", 1800000);

	set_skill("force", 260);
	set_skill("dodge", 235);
	set_skill("parry", 240);
	set_skill("finger", 250);
	set_skill("tiannan-step", 235);
	set_skill("kurong-changong", 260);
	set_skill("duanshi-xinfa", 260);
	set_skill("sun-finger", 250);
	set_skill("literate", 200);
	set_skill("buddhism", 200);
	set_skill("lamaism", 200);

	map_skill("force", "kurong-changong");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "sun-finger");
	map_skill("finger", "sun-finger");

	prepare_skill("finger","sun-finger");

	set("inquiry" ,([
		"������" : (: ask_me :),
		"��������" : (: ask_me :),
		"�����񽣽���" : (: ask_me :),
	]));
	create_family("����μ�", 14, "��ɮ");

	set_temp("apply/damage", 50);
	set_temp("apply/armor", 50);

	setup();
	carry_object("/clone/cloth/seng-cloth")->wear();
}

int remove_killer(object ob)
{
	object env;

	::remove_killer(ob);

	if (sizeof(query_killer())) return 1;

	env = environment();
	if (env->query("exits")) return 1;

	message_vision("$N̾��һ����������������������ɱ��"
		       "����Ȼ��������ħ��Ҳ���޷���\n",
		       this_object());

	open_exit();
	return 1;
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("shen") < -5000)
	{
		command("say ��ħ��̫�أ����Ǻú÷�ʡһ�°ɡ�");
		return -1;
	}

	if (skill == "literate")
	{
		command("say ��Ǹ����ѧ�Ļ���ȥ�ҽ���������");
		return -1;
	}

	if (! query_skill(skill, 1))
	{
		command("say �ٺ٣���ɮ���ᣬ����������ɡ�");
		return -1;
	}

	if (skill != "lamaism" && skill != "buddhism")
	{
		command("say ���˲�Ҫһζ���ͺ�ɱ����ѧһЩ"
			"ɱ���������似��");
		return -1;
	}

	if (ob->query_temp("mark/����"))
		return 1;

	command("nod");
	command("say �ã��Ҿͺ���̸̸һЩ�𷨷������ᡣ");
	ob->set_temp("mark/����", 1);
	return 1;
}

int ask_me()
{
	object me;

	me = this_player();
	if (me->query("born_family") != "���ϻ���")
	{
		message_vision("$N��Цһ������" +
			       RANK_D->query_respect(this_player()) +
			       "������������������֮����ʲô��\n",
			       this_object());
		return 1;
	}

	message_vision("$N��Ȼ��$n��������Ȼ�ǻ���֮�ˣ�����Ҳ��"
		       "��Ⱦָ�����񽣽��ס�\n", this_object(), me);
	return 1;
}

int accept_fight(object ob)
{
	command("say ��û����Ȥ�����ܡ�");
    	return 0;
}

int accept_touxi(object ob)
{
	command("heng");
	command("command ������");
	start_fight(ob);
    	return 1;
}

int accept_hit(object ob)
{
	command("heng");
	command("command ��Ҫ����ô��");
	start_fight(ob);
    	return 1;
}

int accept_kill(object ob)
{
	command("haha");
	command("say ���ĺã����Ǿͽ���һ����");
	start_fight(ob);
	return 1;
}

int accept_ansuan(object ob)
{
	return notify_fail("��������ׯ�ϣ��㲻��óȻ���֡�\n");
}

void start_fight(object me)
{
	object *obs, ob;
	string msg;
	int i;

	if (!living(this_object()))
		return;

	if (base_name(environment()) != query("startroom") ||
	    is_killing(me->query("id")))
	{
		command("say �Ǿʹ�ɡ�");
		return;
	}

	if (is_fighting())
	{
		command("chat ������" + me->query("name") +
			"����" + RANK_D->query_rude(me) +
			"Ҳ�����ң�");
	} else
	{
		command("chat �ߣ������" + me->query("name") +
			"����ȻҪ�����������µİ�����������"
			"�����ɣ�");
	}

	obs = ({ });
	msg = 0;
	for (i = 0; i < sizeof(names); i++)
	{
		if (! objectp(ob = present(names[i])))
			continue;

		if (! living(ob))
			continue;

		obs += ({ ob });
		if (! msg)
			msg = ob->name();
		else
			msg += "��" + ob->name();
	}

	if (msg)
		command("say " + msg + "�����һ���������ɱ�ˣ�");
	else
		command("say Ҳ�գ�������ɮ����������ɣ�");

	obs->kill_ob(me);
	kill_ob(me);
	close_exit();
}

void die(object killer)
{
	object ob;
	object kob;

	if (! objectp(kob = killer))
		kob = query_last_damage_from();

	ob = find_object(BOOK);
	if (! objectp(ob))
		ob = load_object(BOOK);

	if (! environment(ob))
	{
		ob->move(this_object(), 1);
		command("chat �����벻���ҿ������ܣ����������µ�����������������֮�֣�");
		CHANNEL_D->do_channel(this_object(), "rumor", "��˵" +
			(objectp(kob) ? kob->name(1) : "ĳ��") +
			"���������£���ս��ɮ�������������ס�");
	} else
		command("chat ���ģ��벻���ҿ��ٱ������裬����������ɥ���֣�");

	open_exit();
	::die(killer);
}

void unconcious()
{
	die(0);
}

void close_exit()
{
	object room;
	object here;

	here = environment();
	room = find_object("/d/tianlongsi/banruotai");
	if (! room) room = load_object("/d/tianlongsi/banruotai");

	if (! here->query("exits"))
		return;

	message_vision("$N����һ�ƣ���ʱ�����ű��ϡ�\n", this_object());
	here->delete("exits");

	if (room)
	{
		message("vision", "��Ȼ���顱��һ��" +
			room->query("short") + "�Ĵ��ű����ˡ�\n", room);
		room->delete("exits/south");
	}
}

void open_exit()
{
	object room;
	object here;

	here = environment();
	room = find_object("/d/tianlongsi/banruotai");
	if (! room) room = load_object("/d/tianlongsi/banruotai");

	if (here->query("exits"))
		return;

	message("vision", "���š�֨ѽ֨ѽ���Ĵ��ˡ�\n", here);
	here->set("exits/north", "/d/tianlongsi/banruotai");

	if (room)
	{
		message("vision", "��Ȼ" + room->query("short") +
			"�Ĵ��š�֨ѽ֨ѽ���Ĵ��ˡ�\n", room);
		room->set("exits/south", "/d/tianlongsi/munitang");
	}
}
