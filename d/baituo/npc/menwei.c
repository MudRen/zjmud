//menwei.c
inherit NPC;
inherit F_GUARDER;

void greeting(object);
void init();
void create()
{
	set_name("����", ({ "men wei", "wei"}) );
	set("nickname", "��ʨ��");
	set("gender", "����" );
	set("age", 22);
	set("long", "���Ǹ��긻��ǿ������������ʮ�����ϡ���Ȼ�������ղ��ߣ�����\n"
		    "����ŷ�����ѵ�������ǳ��˿ɵС�\n");
	set("attitude", "friendly");
	set("shen_type", -1);

	set("str", 23);
	set("int", 23);
	set("con", 22);
	set("dex", 20);

	set("max_qi", 1200);
	set("max_jing", 600);
	set("neili", 1700);
	set("max_neili", 200);
	set("combat_exp", 50000 + random(50000));
	set("score", 10000);

	set_skill("force", 100);
	set_skill("dodge", 80);
	set_skill("unarmed", 80+random(10));
	set_skill("parry", 90);
	set_temp("apply/attack", 45);
	set_temp("apply/defense", 45);
	set_temp("apply/damage", 50);
	set_temp("apply/armor", 50);

	set("coagents", ({
	    ([ "startroom" : "/d/baituo/dating",
	       "id"	: "ouyang feng" ]),
	}));

	create_family("ŷ������", 0, "����");

	setup();
	add_money("silver",20);
	carry_object("/d/baituo/obj/dadao")->wield();
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	if(check_family(ob, "ŷ������"))
	{
		say("����Ц������˵������λ" + RANK_D->query_respect(ob) +
		    "�������ˣ�������ɡ���\n");
		return;
	}

	if((int)ob->query("shen") > 200)
	{
		say("��������һ�ɣ�˵������λ" + RANK_D->query_respect(ob) +
		    "���������鷳�İɡ�\n����ׯ���񹦸�����Ȱ�㲻Ҫ���������\n");
		return;
	}
}
