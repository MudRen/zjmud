// dizi1 ³��  
// Modify By River@SJ
// Modified by snowman@SJ 22/11/2000
// ����flood

#include <ansi.h>

inherit NPC;
string *names = ({"��ɨ��", "��ľͷ", "����", "��Ȳ˵�", "����", "��ˮ"});
string *address = ({"���", "ľ��", "��", "��԰", "�˵�", "ˮ��"});
string ask_job();
int do_task();

void create()
{
	set_name("³��", ({ "lu kun","lu","kun", "man" }));
	set("title", "������ݴ����");
	set("gender", "����");
	set("age", 35);  
	set("long", "��������ɽ�Ĵ���ӣ�Ҳ�ǹ��������ε�ͽ�ܣ��������񰺰���\n");
	set("combat_exp", 10000);
	set("shen_type", 1); 
	set("unique", 1);

	set_skill("force", 70);
	set_skill("strike", 70);
 
	set("inquiry",([
		"����" : (: ask_job :),
		"����" : (: do_task :),
		"����" : "��ȥ��Ʒ���������⿲Ҫ�ɣ�", 
	]));
	setup();
}

void init()
{
	object ob;
	::init();
	if( interactive(ob = this_player()) && !is_fighting()){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

string ask_job()
{
	int size, i;
	string target, str;
	object ob = this_player();

	if(ob->query_temp("job_name"))
		return "�㲻���Ѿ����˹����𣿻�����ȥ����";

	if(ob->query("combat_exp") > 10000)
		return "�㹦���Ѿ�ͦ���ˣ�����û��ʲô�ʺ���Ĺ����ˡ�";

	if ( ob->query_temp("jobover") == 5 )
		return "�����ֵ��������㣬�㻹����ȥ�����ɡ�";

	size = sizeof(names);
	i = random(size);
	target = names[i];
	ob->set_temp("job_name",target);
	str = "�����ݺ�æ����������Ʒ����ù��ߣ�Ȼ��ȥ"+ address[i] +target+ "�ɡ�";
	if ( ob->query_temp("need_answer"))
		str += "\n��Ʒ����"+address[i]+"��λ�ã������ͨ�� help map wuguan Ѱ�ҡ�";
	tell_object(ob, CYN"³��˵������"+str +"��"NOR"\n");
	return "��λ"+RANK_D->query_respect(ob)+"�ֽ������㣬����������˺��Ҹ���һ�¡�";
}

int do_task()
{
	object ob,me;
	int pot;
     string arg="ok";
  	
	ob = this_player();
	me = this_object();
	
	if( !arg || arg != "ok" ) return 0;
	if( !ob->query_temp("job_name") ){
		tell_object(ob, CYN+me->name()+"˵������û���㹤��������ô���������ˣ���"NOR"\n");
		return 1;
	}
	if(!ob->query_temp("mark/����")){ 
		tell_object(ob, CYN+me->name()+"˵���������Ȱѹ��߻������ܣ����������ɡ���"NOR"\n");
		return 1;
	}
	if(!ob->query_temp("mark/����")){
		tell_object(ob, CYN+me->name()+"˵��������͵����������ɻ��㲻ȥ�ɣ������칦����"NOR"\n");
		return 1;
	}
	if( arg=="ok" && ob->query_temp("mark/����")){
		command("smile "+ob->query("id"));
		tell_object(ob, CYN+me->name()+"˵�������ã�"+RANK_D->query_respect(ob)+"�����úã����Ǹ���Ľ��ͣ���"NOR"\n");
		if (random(10) < 6){
			me->add_money("coin",(int)(ob->query_skill("force",1)/2)+50);
			command("give "+ob->query("id")+" "+((int)(ob->query_skill("force",1)/2)+50)+" coin");
		}
		else{
			me->add_money("silver",(int)(ob->query_skill("force",1)/5)+1);
			command("give "+ob->query("id")+" "+((int)(ob->query_skill("force",1)/5)+1)+" silver");
		}
		pot = ob->query_skill("force",1)/3 + 10;		
		pot = pot + 40;
		pot = ob->add_exp_combat(pot,this_object(),"���");
		pot = pot - 40;
		if(pot < 0 ) pot = 1;						
		ob->add("potential",pot);
		
		ob->delete_temp("job_name");
		ob->delete_temp("mark");
		tell_object(ob,HIW"�㱻�����ˣ�"+chinese_number(pot + 40)+"�㾭���"+chinese_number(pot)+"��Ǳ�ܡ�"NOR"\n");
		if(ob->query_temp("wg/lujob") < 5) {
			ob->add_temp("wg/lujob",1);
		} 
		else {
			if(ob->query_temp("jobover") != 5 && ob->query_temp("need_answer")) {
				tell_object(ob, CYN"³��˵��������˵�����ֵܻ��е��������㣬�����ȥ��һ�¡���"NOR"\n");
				ob->set_temp("jobover", 5);
				ob->delete_temp("wg/lujob");
			}
		}
		return 1;
	}
	return 1;
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if(ob->query_temp("mark/����")
	 && ob->query_temp("job_name")){ 
		command("nod " +ob->query("id"));
		tell_object(ob, CYN"³��˵������"+ob->name()+"���㹤�����ò������Ը��Ҹ����ˡ���"NOR"\n");
		return;
	}
	if ( ob->query("combat_exp") < 3000 
	&& !ob->query_condition("wuguan_job")
	&& !ob->query_temp("job_name")
	&& (ob->query_temp("jobask") == 5 || ob->query("combat_exp") >= 400) ) {
		command("pat "+ob->query("id"));
		tell_object(ob, CYN"³��˵��������λ"+ RANK_D->query_respect(ob)+ "��������ȱ���֣�����������칤����������"NOR"\n");
	}
}
