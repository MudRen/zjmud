// xiejian.c а������

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "li si", "li" }) );
	set("title", "С���ϰ�");
	set("gender", "����" );
	set("shen_type", -1);
	set("age", 40);

	set("str", 30);
	set("con", 30);
	set("int", 30);
	set("dex", 30);

	set("long",
		"��������Ц�����С���ϰ壬��Ȼ����ʲ�ᶫ����ȴҲ�������ڡ�\n" );

	set("combat_exp", 100000);
	set("attitude", "peaceful");
	set("chat_chance", 1);
	set("chat_msg", ({
		"����˵��: ��λ�͹٣�������Щʲ�ᶫ���� ?\n",
	}) );

	set("inquiry", ([
		"а��"   : "���Ѿ������ˣ����������ˡ�",
		"ɱ��"   : "���Ѿ������ˣ����������ˡ�",
	]) );

	set("max_qi", 700);
	set("max_jing", 400);
	set("neili", 700);
	set("max_neili", 700);
	set("jiali", 50);
	set("shen_type", -1);
	set("env/wimpy", 60);

	set_skill("force", 60); 
	set_skill("unarmed", 80);
	set_skill("sword", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	
	setup();
	
	carry_object("d/city/obj/gangjian")->wield();
	carry_object("d/city/obj/cloth")->wear();
}

