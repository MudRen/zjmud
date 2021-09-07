// city/npc/angelus.c

inherit NPC;
inherit F_DEALER;
string do_level_up();
void create()
{
	set_name("��������", ({ "shen mi"}));
	set("level_up",1);
	set("gender", "����");
	set("age", 20);
	set("per", 30);
	set("con", 30);
	set("int", 30);
	set("level", 99);
	set("dex", 30);
	set("str", 30);
	set("long","�������ˣ����ո����鼮����װ������ͬʱ����һЩ��װ��\n");
	set_skill("unarmed", 600);
	set_temp("apply/damage", 150);
	set("inquiry", ([
		"����": "����ж����<��װ>��<�鼮>,���Ը��һ�ȡ<�һ���>",
	]) );
	set("combat_exp", 500000);
	set("attitude", "friendly");
	set("duihuan",1);
	set("vendor_goods", ({
	       "/clone/suit/wudang/zhenwu_sword",
	      "/clone/suit/wudang/zhenwu_finger",
	      "/clone/suit/wudang/zhenwu_arrmor",
	      "/clone/suit/wudang/zhenwu_neck",	
	      "/clone/suit/wudang/zhenwu_head",
	      "/clone/suit/wudang/zhenwu_hands",
	      "/clone/suit/wudang/zhenwu_pants",
	      "/clone/gift/jiuzhuan",
	      "/clone/gift/unknowdan",
	       "/clone/gift/xisuidan",
	       "/clone/gift/shenliwan",
		"/clone/gift/xiandan",
	       "/clone/gift/mdiamond",
	}));
	
	setup();
	carry_object(__DIR__"cloth/cloth")->wear();
}

void init()
{
	add_action("do_level_up","level_up");
	add_action("do_up_skills","up_skills");
	add_action("do_up_tianfu","up_tianfu");
	add_action("do_pointlist", "list");
	add_action("do_huan", "huan");
}
//������װ.
int accept_object(object who, object ob)
{
      int suit_point=0,suit_level=0;
      mapping book=([ ]);
	if(ob->query("skill")) book=ob->query("skill");
	if(ob->query("suit"))
	{
	    suit_level=(int)ob->query("suit_lvl");
	    if(suit_level != 1)
	    {
	       suit_point=random(suit_level*10)+1;
	    }
	    else
	    {
	       suit_point=random(suit_level*2)+1;
	    }	
//	    who->add("suit_point",suit_point);
	    message_vision(HIG"�������˶�����ͷ,�����װ������,< "+HIM+suit_point+HIG+" �һ��� > �Ѿ������ˡ�"NOR"\n", who);
	    destruct(ob);
	    return 1;
	}
	if(book["max_skill"])
	{
	    suit_level=(int)ob->query("value")/10000;
	    suit_point=random(suit_level)+1;
//	     who->add("suit_point",suit_point);
	    message_vision(HIG"�������˶�����ͷ,�Ȿ��������,< "+HIM+suit_point+HIG+" �һ��� > �Ѿ������ˡ�"NOR"\n", who);
	    destruct(ob);
	    return 1;
	}
	    command("say �ⲻ����װ���鼮,�Ҳ����գ�");
	    return 0;
}
