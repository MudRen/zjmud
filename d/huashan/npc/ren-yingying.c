// ren-yingying.c

inherit NPC;

void create()
{
	set_name("��ӯӯ", ({ "ren yingying", "yingying" }) );
	set("title","ħ��ʥ��");
	set("gender", "Ů��" );
	set("age", 19);
	set("str", 16);
	set("con", 30);
	set("int", 30);
	set("dex", 30);

	set("attitude", "friendly");

	set("qi",2500);
	set("max_qi",2500);
	set("jing",1200);
	set("max_jing",1200);
	set("neili", 2800);
	set("max_neili", 2800);
	set("jiali", 30);

	set("long",     "��ӯӯ��ħ�̽��������еĶ���Ů����\n");
	set("combat_exp", 250000);
	set("shen_tpye", 1);
	set_skill("unarmed", 90);
	set_skill("sword", 90);
	set_skill("force", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	set_skill("literate", 100);

	set_skill("huashan-sword", 100);
	set_skill("huashan-xinfa", 100);
	set_skill("huashan-quanfa", 100);
	set_skill("feiyan-huixiang", 100);

	map_skill("sword", "huashan-sword");
	map_skill("parry", "huashan-sword");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "feiyan-huixiang");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();

}

int accept_fight(object me)
{
	command("say СŮ����������Ķ���?");
	return 0;
}
void init()
{
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting",2 , ob);
	}
}
void greeting(object ob)
{
      say( "��ӯӯ΢΢̾�˿���������֪���ҵ��������ںη�?��\n");
      if ( ((int)ob->query_dex()>=25) && ((int)ob->query_int()>=25) )
      {
	   tell_object(ob,"��ӯӯ˵������������ҵ���������.\n");
	   ob->set("marks/feng-qingyang",1);
      }
      tell_object(ob,"��ӯӯ������仰��ƮȻ��ȥ.\n");
      call_out("goway",10);
}
void goway(){
      destruct(this_object());
}
