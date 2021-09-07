#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�Ŵ�ɽ", ({ "zhang cuishan", "zhang" }));  
	set("long",
	"һ����ʮһ��������꣬��Ŀ���㣬��Ȼ�Ծ���\n"
	"񳣬��������ˬ�����ε��������ڲ�סһ���⺷\n"
	"֮�⡣\n");
	set("attitude", "heroism");
	set("title", "�䵱����");
	set("nickname", WHT"��������"NOR);
	set("per", 30);
	set("age", 21);
	set("shen_type", 1);
	set("combat_exp", 1400000);
	set("score", 60000);

	set_skill("unarmed", 200+random(50));
	set_skill("parry", 200+random(50));
	set_skill("dodge", 200+random(50));

	create_family("�䵱��", 2, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/beijing/npc/obj/cloth1")->wear();
}
int accept_fight(object who)
{
	command("say ���ǲ�������ܵģ�");
	return 0;
}
int accept_hit(object who)
{
	command("say ���ǲ�������ܵģ�");
	return 0;
}
int accept_kill(object who)
{
	command("say ��ô��Ҫ����ô������������ɲ����㣡");
	return notify_fail("ɲ�Ǽ�����û��ǲ�Ҫ�������Ϊ�á�\n");
}
int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ���᳡���ѹѹ�ļ������ˣ��������������\n");
}
void receive_damage(string type, int n)
{
	return;
}
void receive_wound(string type, int n)
{
	return;
}
int begin(object me)
{
	if (me->query_temp("biwu"))
	return notify_fail("���ںͱ��˱����أ���ʲô����\n");

	me->set_temp("biwu",1);
	command("say �����书��ǿ������ִ�������ȥ��ȴ�����˵���һ���˵�������");
	message_vision(CYN "$N˵�������ʸ�����˭��ƾʲô���ҷ���ʩ������������Ա��ԡ�"NOR"\n", me);
	message_vision(CYN "$N˵�������С�ȭ�š��ڹ����������Ṧ��ˮ���������һ׮�������Լ������Ҷ����㡣"NOR"\n", me);
	remove_call_out("biwu");
	call_out("biwu",3,me);
	me->set_temp("bizhang",1);
	return 1;
}
void biwu(object me)
{
	command("say �Ҳ��Ǹ���ȱ��У�ֻ�Ǳ�д�����֡�");
	message_vision(HIR "\n�Ŵ�ɽ˵�Ż����ߵ�����ɽ��ǰһ�´�ʯ��ǰ����һ�������͵���˫��һ�ţ��������"NOR"\n",this_object());
	remove_call_out("biwu2");
	call_out("biwu2",8,me);
}
void biwu2(object me)
{
	message_vision(HIR "\n�Ŵ�ɽ�����������࣬����ʹ���������ݡ��������ҽ���ɽ��һ�ţ�һ���������������ɡ�"NOR"\n",this_object());
	message_vision(HIR "\n�����йٱʿ�׼ʯ�棬�����ͼ�������д��һ����"NOR+HIY"��"NOR+HIR"���֡�"NOR"\n",this_object());
	message_vision(HIR "\n�Ŵ�ɽһ����д�꣬���ӱ�Ҫ���£�ͻȻ���ֻӳ����������գ�ٿ��һ������ס��ʯ�ڵķ�϶��"NOR"\n",this_object());
	message_vision(HIR "\n���÷�϶֧ס���ӵ����������ָ�����д�˸���"NOR+HIY"��"NOR+HIR"���֡�"NOR"\n",this_object());
	remove_call_out("biwu3");
	call_out("biwu3",8,me);
}
void biwu3(object me)
{
	message_vision(HIR "\n�Ŵ�ɽ������д�գ�������д��"NOR+HIY"��"NOR+HIR"���֣���"NOR+HIY"��"NOR+HIR"���֡�ԽдԽ�죬����ʯм�׷׶��¡�"NOR"\n", this_object());
	message_vision(HIR "\n�ּ������������ڣ����������������������ʮ����һ��д�ϡ�"NOR"\n", this_object());
	message_vision(HIR "��һ��ʯ�ڿ��飬���������ʫ�ƣ�\n"NOR"\n",this_object());
	message_vision(HIW "	    Ʈ�����꾪�쪣��仨��ѩ��ãã��"NOR"\n", this_object());
	message_vision(HIW "	    ������ڲ�ͣ�֣�һ�����ִ��綷��"NOR"\n", this_object());
	message_vision(HIW "	    �л����Ź��񾪣�ʱʱֻ�������ߡ�"NOR"\n", this_object());
	message_vision(HIW "	    ���������羪�ף�״ͬ�����๥ս��"NOR"\n", this_object());
	message_vision(HIR "\n�Ŵ�ɽд�����桱�ֵ����һ�ʣ�������ʯ����һ�ţ�������أ��������ɵ��������������ԡ�"NOR"\n", this_object());
	message_vision(HIR "\n$N������ʯ���������д��֣��������ã�û��������"NOR"\n", me);
	remove_call_out("shu");
	call_out("shu",4,me);
}
void shu(object me)
{
	message_vision(HIR "\n$N����̾��һ������˵��������д�������������ˡ���"NOR"\n", me);
	message_vision(CYN "$N˵���������ʸ����кηԸ�����"NOR"\n", me);
	me->delete_temp("bizhang");
	me->set_temp("shu",1);
	remove_call_out("end");
	call_out("end",5,me);
}
void end(object me)
{
	mixed *files;
	string file;
	object *inv,room;
	int i,j;
	object ding,dao;
	object obj = present("yin susu");

	command("say ������ʤ�ˣ���������һ���˵�������");
	command("say �߰�");
	me->delete_temp("biwu");
	ding = present("ding", environment());
	dao = present("tulong blade", ding);
	if (objectp(dao))
	{
		command("rumor "+me->name(1)+"������ɽ�����˸�·Ӣ�������������������");
		if (! me->query("guan/�����ﵶ������"))
		{
			me->add("combat_exp", 20000);
			me->add("potential", 500);
			me->add("weiwang", 10000);
			me->add("score", 5000);
		}
		me->set("guan/�����ﵶ������", 1);
		dao->move(me, 1);
	      tell_object(me,HIW"\n��õ�������������\n\n");
	}

	message_vision(HIC"\n$N��$n�������ϴ����﷫��ȥ��"NOR"\n",me,this_object());
	if (objectp(obj)) obj->move("/d/tulong/tulong/boat");
	this_object()->move("/d/tulong/tulong/boat");
	me->move("/d/tulong/tulong/boat");
	me->delete_temp("bishi");
	remove_call_out("storm");
	call_out("storm",random(30),me);
}
void storm(object me)
{
	message_vision(HIB "\nͻȻ֮�䣬$N����һ�࣬���˼���ת��ֻ���ü����Х��"NOR"\n",this_object());
	message_vision(HIB "���˺��֮�����ƺ�ǧ�ٸ�����ͬʱϮ����"NOR"\n",this_object());
	remove_call_out("storm2");
	call_out("storm2",4,me);
}
void storm2(object me)
{
	message_vision(HIB "\n�ŵ��²հ嶷Ȼ�������ȥ�����еĺ�ˮ�����⵹к��"NOR"\n",this_object());
	message_vision(HIB "�����ÿ���Х�����ܾ��Ǻ�ˮ��"NOR"\n",this_object());
	remove_call_out("storm3");
	call_out("storm3",4,me);
}
void storm3(object me)
{
	message_vision(HIB "\n������������ɢ����¶����ҹ֮�⡣"NOR"\n",this_object());
	message_vision(HIB"\n������������Ʈ����"NOR"\n",this_object());
	remove_call_out("storm4");
	call_out("storm4",4,me);
}
void storm4(object me)
{
	message_vision(HIB "\n������������Ʈ����"NOR"\n",this_object());
	remove_call_out("storm5");
	call_out("storm5",4,me);
}
void storm5(object me)
{
	message_vision(HIB "\n������������Ʈ����"NOR"\n",this_object());
	remove_call_out("storm6");
	call_out("storm6",4,me);
}
void storm6(object me)
{
	message_vision(HIB "\n������������Ʈ����"NOR"\n",this_object());
	remove_call_out("arrive");
	call_out("arrive",4,me);
}
void arrive(object me)
{
	object obj = present("yin susu");
	message_vision(HIY "ֻ��������һ�������ⷽʻ���������ص���ԭ�ˡ�"NOR"\n",this_object());
	message_vision(CYN "�Ŵ�ɽ��ȭ˵�������Ǿʹ˱����������ڡ�"NOR"\n",me,this_object());
	me->move("/d/tulong/tulong/boat3");
	if (objectp(obj)) 
		destruct(obj);
	destruct(this_object());
	
}
void init()
{
       add_action("do_get", "get");
}
int do_get(string arg)
{
       object obj,env,ding;
       string what,where;
       if(!arg)
       return 0;
	if (!this_player()->query_temp("bishi", 1))
		return 0;
       if(sscanf(arg,"%s from %s",what, where) !=2)
       return 0;
       if(objectp(present("mai jing", environment())) || objectp(present("guo sanquan",environment())))
       return 0;
	if(what == "tulong blade"||what == "blade"||what == "dao"||what == "tulong" || where =="ding")
       {
	      message_vision(CYN "$N˵���������䵱�Ŵ�ɽ�����������ˣ�"NOR"\n",this_object());
	      this_player()->delete_temp("bizhang");
	      begin(this_player());
	      return 1;
       }
       return 0;
}

