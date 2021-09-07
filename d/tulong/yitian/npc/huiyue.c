#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	object ling3;
	set_name("����ʹ", ({ "huiyue shi", "huiyue", "shi" }));
	set("long", "һ����ʮ������������ӣ�װ�����죬��ͬ\n"
		    "��ͨ��������ʿ������ǲ�˹�����ܽ̽���\n"
		    "���µĻ���ʹ��\n");
	set("title", HIB "��˹�ܽ̽�������" NOR);
	set("nickname", HIY "�Ʒ�����ʹ" NOR);
	set("gender", "����");
	set("age", 38);
	set("attitude", "friendly");
	set("shen_type", 1);

	set("per", 30);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 2500);
	set("max_jing", 800);
	set("neili", 2600);
	set("max_neili", 2600);
	set("jiali", 100);
	set("combat_exp", 800000);

	set("chat_chance_combat", 200);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("literate", 100);
	set_skill("sanscrit", 300);
	set_skill("force", 180);
	set_skill("dodge", 180);
	set_skill("unarmed", 180);
	set_skill("parry", 180);
	set_skill("finger", 220);
	set_skill("strike", 220);
	set_skill("sword", 180);
	set_skill("shenghuo-ling", 180);
	set_skill("tougu-zhen", 220);
	set_skill("yinfeng-dao", 220);
	set_skill("shenghuo-xinfa", 200);
	set_skill("qiankun-danuoyi", 180);
	set_skill("sanscrit", 200);

	map_skill("dodge", "qiankun-danuoyi");
	map_skill("force", "shenghuo-xinfa");
	map_skill("finger", "tougu-zhen");
	map_skill("strike", "yinfeng-dao");
	map_skill("parry", "qiankun-danuoyi");
	map_skill("sword", "shenghuo-ling");

	prepare_skill("strike", "yinfeng-dao");
	prepare_skill("finger", "tougu-zhen");

	create_family("��˹�����ܶ�", 32, "����");

	setup();

	if (clonep())
	{
		ling3 = find_object("/clone/book/ling3");
		if (! ling3) ling3 = load_object("/clone/book/ling3");
		if (! environment(ling3))
			ling3->move(this_object());
			ling3->wield();
	}

	carry_object(__DIR__"obj/jiaofu")->wear();
}

void init()
{
	object me;

	me = this_player();

	if (! interactive(me))
		return;

	if (living(this_object()) && present("yitian sword", me))
	{
		command("say �ף����콣��ô������������������ԭ֮��û�����ˣ�");
		kill_ob(me);
		return;
	}

	if (living(this_object()) && present("tulong blade", me))
	{
		command("say �ߣ����������������������Ѿ��غ��ʱ�ˣ�");
		kill_ob(me);
		return;
	}

	if (living(this_object()) && present("shenghuo ling", me))
	{
		command("say �ף�����ô�������ҽ̵�ʥ������ɣ�");
		kill_ob(me);
		return;
	}
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("shen") > 1000)
	{
		command("say ߴ������������³³�������˿���ȥ�����Ǻ��ˣ�������");
		return -1;
	}

	if (skill != "sanscrit")
	{
		command("say ���������ӡ��ѧ��һ�㶫�����㻹��֪�㰡��");
		return -1;
	}

	return 1;
}

