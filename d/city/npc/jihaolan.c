// ���ſʹ���
// jihaolan.c
// creat by shure@tomud.com 2010-02-18

inherit NPC;
inherit F_DEALER;

string ask_form(string name);
string ask_start();
void create()
{
	set_name("�ĺ���", ({"ji haolan"}));
	set("gender", "Ů��");
	set("nickname", HIB"��������"NOR);
	set("age", 21);
	 set("icon", "01394");
	set("long",
		"�������Ա���,�������Ů��,����������š�\n"
		"��ÿ�궼��������������һ�⣬����һЩ������Ϥ��Ϸ��̽����̬���顣\n"
		"���������������"HIR"��Ϸ����"NOR"������\n"
		"���������Ը��������Ŷ!\n");

	set("startroom", "/d/city/guangchang");
	set("inquiry", ([
		"������ָ�ϡ�"       : (: ask_form ,"newbie" :),
		"������������"       : (: ask_start :),
	]) );
	set("duihuan",1);  //�һ�
	set("vendor_goods", ({
	       "/clone/misc/shi",
	       "/clone/gift/jinkuai",
	       "/clone/gift/cagate",
	       "/clone/gift/ccrystal",
	       "/clone/gift/cdiamond",
	       "/clone/gift/cjade",
	       "/clone/suit/huashan/ling_boots",
	       "/clone/suit/huashan/ling_cloth",
	       "/clone/suit/huashan/ling_pants",
	       "/clone/suit/huashan/ling_sword",
	}));
	setup();
	carry_object("/clone/cloth/cloth")->wear();
}
void init()
{
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
	    message_vision(HIG"���������ͷ,�����װ������,< "+HIM+suit_point+HIG+" �һ��� > �Ѿ������ˡ�"NOR"\n", who);
	    destruct(ob);
	    return 1;
	}
	if(book["max_skill"])
	{
	    suit_level=(int)ob->query("value")/10000;
	    suit_point=random(suit_level)+1;
//	     who->add("suit_point",suit_point);
	    message_vision(HIG"���������ͷ,�Ȿ��������,< "+HIM+suit_point+HIG+" �һ��� > �Ѿ������ˡ�"NOR"\n", who);
	    destruct(ob);
	    return 1;
	}
	    command("say �ⲻ����װ���鼮,�Ҳ����գ�");
	    return 0;
	
      
}
string ask_form(string name)
{
	object me;
	object ob;

	me = this_player();
	if( me->query("mud_age") > 102000 )
		return "���Ѿ��������ˡ�";
	if (present(name, this_player()))
	return RANK_D->query_respect(this_player()) + "�����ϲ����Ѿ�������"; 
	 ob = new("/clone/misc/newbie");
	
	ob->move(me);
	tell_object( me, HIG"�������ص�Ц��Ц��"NOR"\n" );
	tell_object( me, HIG"����˵��������ҷ����ǰ���������Ϥ��Ϸ�ġ�"NOR"\n" );
	command( "say " + "���ú���ݡ����ְ���ָ�ϡ���" );
	return "����"HIR" read book "NOR + CYN"�Ϳ��Զ�ָ���ˡ�";
}
string ask_start()
{
	object me;
	object ob;

	me = this_player();
if ( me->query("combat_exp", 1) < 10000 ) return "������΢�е�ʵս����������ȡ���ֽ����ɣ�";

       if(!me->query("jiangli"))
       {
	ob = new("/clone/misc/sleepbag");
	ob->move(me);     
	ob = new("/clone/money/gold");
	ob->move(me);  
	me->set("jiangli",1);
	write(HIY"\n����·���У���������Ʒ��"NOR"\n");
	write(HIG"\n��õ��������������� <�ƽ�>: һ��   <����>: һ������лл���� "NOR"\n");
       }
      return HIR+"  һ·˳�磬лл֧��[��������]"+NOR;
}