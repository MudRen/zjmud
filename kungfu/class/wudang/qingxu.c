// guxu.c ����

inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
	set_name("�������", ({ "qingxu daozhang", "qingxu" }));
	set("long", 
		"�����������۵ĵ������������\n"
		"�������ʮ���꣬���ܸ���۵����¡�\n"
		"ר�������￴�ر��ɵĸ��ֵ���");
	set("gender", "����");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 22);
	set("int", 22);
	set("con", 22);
	set("dex", 22);
	
	set("max_qi", 1800);
	set("max_jing", 900);
	set("neili", 2400);
	set("max_neili", 2400);
	set("jiali", 30);

	set("combat_exp", 70000);
	set("score", 8500);

	set_skill("force", 85);
	set_skill("wudang-xinfa", 85);
	set_skill("dodge", 80);
	set_skill("tiyunzong", 80);
	set_skill("strike", 85);
	set_skill("wudang-zhang", 85);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("wudang-jian", 80);
	set_skill("taoism", 50);
  	set_skill("literate", 50);

	map_skill("force", "wudang-xinfa");
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "wudang-jian");
	map_skill("sword", "wudang-jian");
	map_skill("strike", "wudang-zhang");

	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 3, "����");
	set("class", "taoist");

	set("inquiry", ([
			"���¾�" : (: ask_me :),
	]));
				
	set("book_count", 1);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}


string ask_me()
{
	mapping fam; 
	object ob;

	if (!(fam = this_player()->query("family")) 
	    || fam["family_name"] != "�䵱��")
	{
		return RANK_D->query_respect(this_player()) + 
		       "�뱾��������������֪�˻��Ӻ�̸��";
	}

	if (query("book_count") < 1)
		return "�������ˣ����ɵĵ����澭���ڴ˴���";

	add("book_count", -1);
	ob = new("/clone/book/daodejing-ii");
	ob->move(this_player());
	return "�ðɣ��Ȿ�����¾������û�ȥ�ú����С�";
}
