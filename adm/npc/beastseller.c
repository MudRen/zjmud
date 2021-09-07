// beastseller.c
#include <ansi.h>
inherit NPC;
inherit F_DEALER;

#define BEAST_OB	  "/clone/npc/magic-beast.c"
#define BEAST_DIR	 "/data/beast/"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_beast(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);
string ask_form(string name);

string* beast_type_name = ({
	"��", "¿", "��", "��", "ţ", "��",
	"ʨ", "��", "��", "¹", "��", "��",
	"��", "��", "��", "��", "��", "��",
	"��", "��", "��",
});

string* beast_id_surfix = ({
	"ma", "lv", "luo", "tuo", "niu", "xiang",
	"shi", "hu", "bao", "lu", "he", "diao",
	"yang", "hou", "xiong", "lang", "hu", "diao",
	"ju", "shou", "long",
});

string* beast_unit_name=({
	"ƥ", "ͷ", "ͷ", "ͷ", "ͷ", "ͷ",
	"ֻ", "ֻ", "ֻ", "ͷ", "ֻ", "ֻ",
	"ͷ", "ֻ", "ֻ", "��", "ֻ", "ֻ",
	"ƥ", "ͷ", "��",
});

void create()
{	
	set_name("����", ({ "shang ren", "ren", "shangren" }) );
	set("gender", "����" );
	set("age", 21);
	set("long",@LONG
�������˴���û��֪������ʲô�ط����ģ�ֻ֪����ͻȻ������
������۸��ָ��ֻ��ޣ����޾��и�������Ĺ��ܣ������ϲ
���Ļ�������Ҳѡ(choose)һֻ��
LONG );
	set("title",HIW"ħ��������"NOR);
	set("combat_exp", 5);
	set("icon","00174");
	set("inquiry", ([ 
		"��ħ���ޡ�"     : "ֻҪ����һ�����ƽ������ӵ��ħ�����ˣ�", 
		"������֮�ڡ�"       : (: ask_form ,"shoushao" :),
	]));
	set("skill_huanshou", 1);
	set_skill("training", 400);    
	set_skill("huisheng-jue", 400);    
	set("chat_chance", 15);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/clone/misc/shi",
	  
	}));
	setup();
	carry_object("/clone/cloth/cloth")->wear();
	create_family("���ﱣ��Э��", 1, "�᳤");      
}

void init()
{       
	object ob;
	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_choose", "choose");
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
string ask_form(string name)
{
	object me;
	object ob;

	me = this_player();
	if (present(name, this_player()))
	return RANK_D->query_respect(this_player()) + "�����ϲ����Ѿ�������";
	 if(me->query("can_whistle"))
	 {
	     ob = new("/clone/misc/huanshou_shao");
	     ob->move(me);
	     tell_object( me, HIG"�����������ص�Ц��Ц��"NOR"\n" );
	     return "���ú����������֮�ڡ��ɡ�" ;
	 }
	 else
	 {
	     return "�������޶�û�У�Ҫ����ʲô������" ;
	 }
	
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(5) ) {
		case 0:
			say( "��������˵������λ" + RANK_D->query_respect(ob)
				+ "��Ҫħ����ô��\n");
			break;
		case 1:
			say( "��������˵������λ" + RANK_D->query_respect(ob)
				+ "��ħ���޿����������������˵�Ŷ��\n");
			break;
	}
}

int do_choose()
{
	object me = this_player();

	if (me->is_busy())
		return notify_fail("����һ��������û����ɡ�\n");
		
	if (file_size(me->query_save_file() + "-beast.o") > 0 &&
	    mapp(me->query("can_whistle")))
		return notify_fail("���Ѿ�ӵ�����İ���ħ�����ˡ�\n");
				   
	if (me->query_skill("training", 1) < 30)
		return notify_fail("���Ԧ������training��̫���ˣ���ʹ����ħ���ޣ�Ҳ�ᱳ�����ȥ��\n��������ѧϰ�ɣ�\n");
	
	if (! me->query_temp("beast/money"))
	{
		command("say ��λ" + RANK_D->query_respect(me) + "��ÿֻħ����һ�����ƽ�������ȸ�Ǯ��");
		return 1;
	}
			       
	write("��Ҫ������ħ���ޣ�\n");
	write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
	write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
	write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
	write("19. ��  20. ��  21. ��\n");
	write("��ѡ�����ִ��ţ�(q ��ȡ��)");
	
	input_to( (: get_subtype :), me);
	return 1;
}

void get_subtype(string arg, object ob)
{
	int n;
   
	if (arg == "q" || arg == "Q")    
		return;

	sscanf(arg, "%d", n);
    
	if (n <= 0 || n > 21)  
	{	       
		write("��Ҫ������ħ���ޣ�\n");
		write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
		write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
		write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
		write("19. ��  20. ��  21. ��\n");	       
		write("�����봿���ִ��ţ�(q ��ȡ��)");
		input_to( (: get_subtype :), ob);
		return;
	}
	ob->set_temp("beast/beast_type", n);

	write("\n");
	write("���趨ħ���޵��Ա�(���ԣ�1  ���ԣ�0)��");
	input_to( (: get_gender :), ob ); 
}

void get_gender(string arg, object ob)
{
	int n;
	object beast;
	
	sscanf(arg, "%d", n);

	if (n != 0 && n != 1)  
	{
		write("\n");
		write("���趨ħ���޵��Ա�(���ԣ�1  ���ԣ�0)��");
		input_to( (: get_gender :), ob );
		return;
	}
	ob->set_temp("beast/beast_gender", n ? "����" : "����");
	  
	write("\n");
	write(sort_string(CYN "�������˵���˵��������Ȼ��ˣ����潫����ħ����"
	      "������ʽ���㲻��Ҫ���κε�������������ȫ���ɣ����Ǹ���"
	      "�ݵ���ʽ���������ֵ�������ʽ��ʼ���� \n��ħ���ޣ�������������һ"
	      "�����ȣ�����������������һ��������ֻ���ӹ����з�������ħ��"
	      "���ѣ���ʱ���������ջع����������Żӳ�һ��������ħ������"
	      "�ϡ�ħ�������ں��������¿�ʼ����ǿ�ҵ�ɧ���������ű�׷�"
	      "Ư�������������ա���ʱ��ŷ���ԭ���ڱ���һ��ħ����������"
	      "�����Ÿ����ħ�����ѣ�ħ�����Ѳ���Ư������ͣ�ڿ���ɢ����"
	      "΢���Ĺ�â������������ϣ��·���Ѱ�����ˣ�ħ������ɲ�Ǽ俪"
	      "ʼ�ڿ������裬һֻħ�������������з������㱾�ܵ����˫��ȥ"
	      "�ӷɵ���ǰ��ħ�����ѡ�"NOR"\n", 64)); 
	write(CYN "\nֻ����������˵��������ʽ��������ϲ�㣡��"NOR"\n"); 
	write(sort_string(CYN "\nֻ�����������ֵ�����������Ŀǰ������ǳ������"
		"����ħ�����ѽ������鹵ͨ���ҾͰ���һ�ΰɡ���"NOR"\n", 64)); 
	write(sort_string(CYN "�㰴�ջ������˵�ָ�㿪ʼ�ɿ�������������ļ�"
		"֤֮�£����������ǻۡ���������һ���ǿ���������ѽ����"
		"������������ԣ������ҵ����ߣ��ң�" + ob->query("name") +
		"��������޽�������Ѫ֮��Լ���մ���Ω��������Ϊ����֮����"
		"��������"NOR"\n", 64));	

	write(sort_string(WHT "ֻ�������еĻ�����ȴ����һ���������������е�ħ"
		"�������¶��쳣�����ߣ������������ֵĸ��£��������������ж�"
		"����ĸо���$N�����ڴ��У�ԭ���⻪����ǿ��ǳ����Ѻۣ�Ȼ"
		"���ѺۼӴ�һ�����أ�˵����������ζ����ʼɢ�����������"
		"�ռ䡣���ţ�һ�����۴�С��ͷ���˳������������е���" + 
		beast_type_name[ob->query_temp("beast/beast_type") - 1] +  "�����ӣ�������������ȫ¶"
		"�˳���������ֻ�а��Ʋ����Ĵ�С��һ��Ӧ������ɫ�ģ�����Ϊմ"
		"����ʪ���Һ����������ɫ��С���޿���$Nһ�ۣ����С��ͷ��"
		"��Ĵָ�����˼��£�����һ���������Ľ������漴��ʼ�����ѿǣ�"
		"һ���ӣ�������������ѿ�һ���Ӿͱ��Թ��ˣ�ֻ�����ɰ��Ĵ���"
		"�����ã�������������������$N�������С�"NOR"\n", 64));
		
	write("\n");
	write("���趨ħ���޵�Ӣ�� id ��");
	input_to( (: get_id :), ob ); 
}

void get_id(string arg, object ob)
{
	arg = lower_case(arg);
	
	if (! check_legal_id(arg))   
	{
		write("\n");
	     
		write("���趨ħ���޵�Ӣ�� id ��");
		input_to( (: get_id :), ob ); 
		return;
	}

	arg = replace_string(arg, " ", "_");    
	
	// ob->set_temp("beast/beast_id", arg + " " + beast_id_surfix[ob->query_temp("beast/beast_type") - 1]);
	ob->set_temp("beast/beast_id", arg);
	ob->set_temp("beast/beast_unit", beast_unit_name[ob->query_temp("beast/beast_type") - 1]);
	
	write("\n");
	write("���趨ħ���޵���������(�ɼ���ɫ���磺$YEL$С��$NOR$ )");
	input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
	string  arg_old;
	string  result;
	
		
	arg_old = arg;
	/*
	arg = trans_color(arg, 1);
	arg = filter_color(arg);
	*/
	arg = replace_string(arg, "$BLK$", "");
	arg = replace_string(arg, "$RED$", "");
	arg = replace_string(arg, "$GRN$", "");
	arg = replace_string(arg, "$YEL$", "");
	arg = replace_string(arg, "$BLU$", "");
	arg = replace_string(arg, "$MAG$", "");
	arg = replace_string(arg, "$CYN$", "");
	arg = replace_string(arg, "$WHT$", "");
	arg = replace_string(arg, "$HIR$", "");
	arg = replace_string(arg, "$HIG$", "");
	arg = replace_string(arg, "$HIY$", "");
	arg = replace_string(arg, "$HIB$", "");
	arg = replace_string(arg, "$HIM$", "");
	arg = replace_string(arg, "$HIC$", "");
	arg = replace_string(arg, "$HIW$", "");
	arg = replace_string(arg, "$NOR$", "");

	if (! check_legal_name(arg, 12))  
	{
		write("���趨ħ���޵���������(�ɼ���ɫ���磺$YEL$С��$NOR$)");
		input_to( (: get_name :), ob);
		return;
	}

	if (stringp(result = NAME_D->invalid_new_name(arg)))
	{
		write("�Բ���" + result);
		write(HIR "��ֹʹ��������������ͬ��ӽ���ħ������������ѭRULES�ж����ֵ���ع涨��"NOR+"\n");
		input_to( (: get_name :), ob);
		return;
	}
	
	arg = arg_old;
	// arg = trans_color(arg, 1); 
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);
	
	ob->set_temp("beast/beast_name", arg);
	
	write("\n");
	write("������ħ���ޣ�(���ɼ���ɫ)");
	input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
		
	if (! check_legal_name(arg, 60))  
	{
		write("������ħ���ޣ�");
		input_to( (: get_desc :), ob);
		return;
	}

	ob->set_temp("beast/beast_desc",  arg);
	write("ok\n");
	build_beast(ob);
}

void build_beast(object ob)
{
	string fc, fn;
	object beast,obj,me;	
	string beast_id;
	string beast_name;
	string beast_unit;
	string beast_desc;
	string beast_gender;

	beast_id = ob->query_temp("beast/beast_id");
	beast_name = ob->query_temp("beast/beast_name");
	beast_name += NOR;
	beast_unit = ob->query_temp("beast/beast_unit");
	beast_desc = ob->query_temp("beast/beast_desc");
	beast_desc += NOR;
	beast_gender = ob->query_temp("beast/beast_gender");
	
	fc = read_file(BEAST_OB);
	
	fc = replace_string(fc, "BEAST_NAME", beast_name);
	fc = replace_string(fc, "BEAST_ID", beast_id);						       
	fc = replace_string(fc, "BEAST_GENDER", beast_gender);			   
	fc = replace_string(fc, "BEAST_UNIT", beast_unit);			  
	fc = replace_string(fc, "LONG_DESCRIPTION", 
			    beast_desc + "\n" + "����" + 
			    ob->query("name") + "��ħ���ޡ�\n");
	
	fc = replace_string(fc, "OWNER_ID", ob->query("id"));
	fc = replace_string(fc, "OWNER_NAME", ob->query("name"));
			    
	fn = BEAST_DIR + ob->query("id") + "-" + "beast";
	
	if (file_size(fn + ".c") > 0)
	{
		if (beast = find_object(fn)) 
			destruct(beast);
		DBASE_D->clear_object(fn);
#ifdef LONELY_IMPROVED
		if (! DATABASE_D->query_db_status())
			DATABASE_D->connect_to_database(); 
		DATABASE_D->db_remove_item(fn);
#endif
		rm(fn + ".c");
	}

	assure_file(fn);
	write_file(fn + ".c", fc); // д���ļ�
	ob->set("can_whistle/" + beast_id, fn);       

	beast = load_object(fn);       
	beast->save();
	destruct(beast);
	me=this_player();
	obj = new("/clone/misc/huanshou_di");
	obj->move(me);
	command("say �����ʹ��[���޵�]�ٻ����ħ���ޣ�<whistle " + beast_id +">\n");
	ob->delete_temp("beast");	
	return;
}

int accept_object(object me, object ob)
{
	string fn;
	string fc;
	object cruise_ob;

	command("xixi");
	command("say �Ǻǣ���л��λ" + RANK_D->query_respect(me) + " ��");

	if (me->query_skill("training", 1) < 30)
	{
		command("say ���Ԧ������������ʹ����ħ���ޣ�Ҳ�������ȥ��");
		return 0;
	}

	if (ob->query("money_id"))
	{
		if (ob->value() < 1000000)
		{
			command("say ��λ����δ�����˵㣡ÿֻħ������Ҫһ�����ƽ�");
			return 0;
		}
		else
		{
			me->set_temp("beast/money",1);
			command("say ���������ˣ�");
			command("say " + me->name() +
				     "�������������и���ħ�����ѣ�");
			command("say ��ѡ����Ҫ��ħ������ < choose >");
			destruct(ob);
			return 1;
		}
	}
	return 0;
}

int check_legal_id(string id)
{
	int i;
	string *legalid;
	object ppl;   
	  
	i = strlen(id);
	
	if ((strlen(id) < 3) || (strlen(id) > 20)) 
	{
		write("�Բ���Ӣ�� id ������ 3 �� 20 ��Ӣ����ĸ��\n");
		return 0;
	}
	
	while(i--)
	
	if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))  
	{
		write("�Բ���Ӣ�� id ֻ����Ӣ����ĸ��\n");
		return 0;
	}

	ppl = LOGIN_D->find_body(id);
	
	if (ppl || id == "guest" || id == "new") 
	{
		write("��������������ID��ͬ�ˣ�����");
		return 0;
	}

	if (file_size(sprintf("/data/user/%c/%s", id[0], id)
		    + __SAVE_EXTENSION__) >= 0) 
	{
		write("��������Ѿ���������ʹ���ˣ�����");
		return 0;
	} 

	return 1;
}

int check_legal_name(string name, int max_len)
{
	int i;
	string  *legalname;	     //not implemented..may add later
	
	i = strlen(name);
	if ((strlen(name) < 2) || (strlen(name) > max_len )) 
	{
		write(sprintf("�Բ���ħ���������ֱ����� 1 �� %d �������֡�\n",
		      max_len / 2));
		return 0;
	}
	
	if (max_len < 13 && ! is_chinese(name))
	{
		write("�Բ��������á����ġ�Ϊ����ȡ���ֻ�������\n");
		return 0;
	}
	return 1; 
}

int attempt_apprentice(object ob)
{
	command("say �߿����������������⣡");
}

int recognize_apprentice(object me, string skill) 
{
	if (skill == "training" || skill == "huisheng-jue") 
		return 1;		
	else 
		return 0;
}

