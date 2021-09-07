// shihou.c ������

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

string ask_me();

void create()
{
	set_name("������", ({ "chuchen zi", "chuchen" }));
	set("nickname", "�����ɰ�ʦ��");
	set("long", 
		"�����Ƕ�����İ˵��ӳ����ӡ�\n"
		"����Ű��֣��������յĸ����ֳ����ء�\n");
	set("gender", "����");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("class", "fighter");
	set("str", 30);
	set("int", 12);
	set("con", 28);
	set("dex", 28);
	
	set("max_qi", 1700);
	set("max_jing", 800);
	set("neili", 2200);
	set("max_neili", 2200);
	set("jiali", 22);
	set("combat_exp", 180000);

	set_skill("force", 120);
	set_skill("huagong-dafa", 120);
	set_skill("dodge", 50);
	set_skill("zhaixinggong", 50);
	set_skill("claw", 50);
	set_skill("sanyin-wugongzhao", 50);
	set_skill("strike", 50);
	set_skill("chousui-zhang", 50);
	set_skill("parry", 120);
	set_skill("staff", 120);
  	set_skill("tianshan-zhang", 120);

	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "chousui-zhang");
	map_skill("claw", "sanyin-wugongzhao");
  	map_skill("parry", "tianshan-zhang");
  	map_skill("staff", "tianshan-zhang");
	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-wugongzhao");

	create_family("������", 2, "����");

	set("coagents", ({
		([ "startroom" : "/d/xingxiu/riyuedong",
		   "id"	: "ding chunqiu" ]),
	}));
	
	setup();
  	carry_object("/clone/weapon/gangzhang")->wield();

}

void attempt_apprentice(object ob)
{
	command("say ���ɻ�û��������ͽ�ء�");
}
