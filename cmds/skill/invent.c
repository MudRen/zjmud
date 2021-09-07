// invent.c

#include <ansi.h>
#include <command.h>
#define  SYN "\""
#define  SYC ".c"
#define  NEED_LVL   600
#define  DEBUG

inherit F_CLEAN_UP;

mapping valid_types = ([
	"unarmed":      "ȭ��",
	"sword":	"����",
	"axe":	  "����",
	"blade":	"����",
	"staff":	"�ȷ�",
	"hammer":       "����",
	"club" :	"����",
	"whip":	 "�޷�",
	"finger":       "ָ��",
	"hand":	 "�ַ�",
	"cuff":	 "ȭ��",
	"claw":	 "צ��",
	"strike":       "�Ʒ�",
]);

mapping type_name = ([
	"unarmed":      "ȭ",
	"sword":	"��",
	"arrow":	"��",
	"axe":	  "��",
	"blade":	"��",
	"staff":	"��",
	"hammer":       "��",
	"club" :	"��",
	"dodge":	"�Ṧ",
	"whip":	 "��",
	"finger":       "ָ",
	"hand":	 "��",
	"cuff":	 "ȭ",
	"claw":	 "צ",
	"strike":       "��",
]);


string *weapon_types = ({
	"sword", "arrow", "axe",
	"blade", "staff", "hammer",
	"club", "whip" , "spin",
});

string *msga = ({ 
	"ڤڤ֮�У�$NͻȻ����",
	"$N�ʾ���֭���ƺ�����",
	"$N��̨һƬ����������",
	"$N��˼��ǰ����ʱ�ĵ��εΣ��ƺ�����",
	"ͻȻ��$N�Ժ����һ�֣�����",
	"$N�����Ȼ�������",
});

string *msgb = ({ 
	"������֮ͨ������������һ����",
	"����һһӡ֤֮����������������������",
	"�ƺ����Ժ϶�Ϊһ����ʱ����һ���ϲ��",
	"�����໥ȡ�����̣�����һ��ȫ�µľ��硣",
	"�������ʹ�����ƺ����Խ��������������ޡ�",
	"�����������������໥�ֲ����в��㣬���������������ʽ��"
});

string *banned_name = ({
	"��", "��", "��", "��", "��", "��",
	"��", "ү", "��", "��",
	"ʺ", "��", "��",
});

string *spe_skill_level = ({
	"0", "12", "20", "30", "40", "50", "60", "80", "100", 
});
		      
string get_skill_name(object me, string skill);
int    skill_t_number(string e_name);
void   finish_write_skill(object ob, string skill);
	
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object  weapon, where;
	mapping skills_map;
	string  msg, invent_skill, *skills, *mut_skills = ({});
	string  *invent;
	int     i;
	
	seteuid(getuid());
	where = environment(me);
	
	if( !arg ) {
		mapping invent_skills;

		if( !mapp( invent_skills = me->query("invent") ) )
			return notify_fail("��Ŀǰ��û���Դ��κ��书��\n");
		
		msg = WHT "��Ŀǰ���� " HIC + chinese_number(sizeof(invent_skills)) + NOR WHT " ���Դ��书��\n";
		invent = keys(invent_skills);
		
		for( i = 0; i < sizeof(invent); i++ )
		{
			msg += CYN "\n��" HIC + to_chinese(invent[i]) + CYN "����" HIY +
			       to_chinese(invent_skills[invent[i]]) +
			       CYN "(" HIY + invent_skills[invent[i]] + CYN ")\n";
		}
		
		tell_object(me, msg);

		return 1;
	}

	if( arg == "?" ) {
	       msg = "�����ǿ����Դ��ļ������ࣺ\n";

	       skills = sort_array(keys(valid_types), (: strcmp :) );
	       for (i = 0; i < sizeof(skills); i++)
			msg += sprintf("  %s (%s)\n", valid_types[skills[i]], skills[i]);
		tell_object(me, msg);

		return 1;
	} else {
		string meskill;
		
		if( sscanf(arg, "%s d", arg) == 1 ) {			
			if( !(meskill = me->query("invent/" + arg)) )
				return notify_fail("û�������Դ��书����ȷ������Ļ����书Ӣ�����ơ�\n");

			tell_object(me, HIR "��ɾ�����Դ��书" + to_chinese(meskill) + "(" + meskill + ")��"NOR"\n");						
			CHINESE_D->remove_translate(meskill);			
			rm( SKILL_D(meskill) + SYC );			
			me->delete_skill(meskill);
			me->delete("invent/" + arg);
			if (! mapp(me->query("invent")) || 
			    sizeof(me->query("invent")) < 1)
				me->delete("invent");
			return 1;
		} else
		if( sscanf(arg, "%s ?", arg) == 1 ) {	 
			mixed  *meskills;	       			
			
			if( !(meskill = me->query("invent/" + arg)) )
				return notify_fail("û�������Դ��书����ȷ������Ļ����书Ӣ�����ơ�\n");
			
			meskills = SKILL_D(meskill)->query_actions();
			msg =  HIW "�Դ��书" + to_chinese(meskill) + "����ϸ�������:"NOR"\n";
			msg += WHT "--------------------------------------------------"NOR"\n";
			msg += HIY "�书��������" + chinese_number(skill_t_number(meskill)) + "��"NOR"\n";
						
			for( i = 0; i < sizeof(meskills); i++ ) {
				msg += WHT "��ʽ" + chinese_number(i + 1) + "���ƣ�" + 
				       meskills[i]["skill_name"] + ""NOR"\n";
				msg += CYN "��ʽ" + chinese_number(i + 1) + "������" + 
				       meskills[i]["action"] + ""NOR"\n";
				msg += CYN "��ʽ" + chinese_number(i + 1) + "������" + 
				       meskills[i]["attack"] + ""NOR"\n";
				msg += CYN "��ʽ" + chinese_number(i + 1) + "�˺���" + 
				       meskills[i]["damage"] + ""NOR"\n";
				msg += CYN "����" + chinese_number(i + 1) + "�˺���" + 
				       meskills[i]["force"] + ""NOR"\n";
				msg += CYN "��ʽ" + chinese_number(i + 1) + "������" + 
				       meskills[i]["dodge"] + ""NOR"\n";
				msg += CYN "��ʽ" + chinese_number(i + 1) + "�мܣ�" + 
				       meskills[i]["parry"] + ""NOR"\n";
			}
			msg += WHT "--------------------------------------------------"NOR"\n";

			tell_object(me, msg);
			return 1; 
		}
				
	}
	   
	if( undefinedp(valid_types[arg]) ) {
		mapping invents;
		string  *invent_skills;

		if( !mapp( invents = me->query("invent") ) )
			return notify_fail("û������������࣬�� invent ? ���Բ鿴����Щ���ࡣ\n");
		
		invent_skills = keys(invents);

		foreach(string str in invent_skills) {
			if( invents[str] == arg ) {
				arg = str;
				invent_skill = invents[str];
				break;
			}
		}

		if( !invent_skill )
			return notify_fail("û������������࣬�� invent ? ���Բ鿴����Щ���ࡣ\n");
	} else {
		if( stringp( invent_skill = me->query("invent/" + arg ) ) )
			return notify_fail("���Ѿ��Դ���һ��" + to_chinese(invent_skill) + 
					   "�����Ҫ����Ϊ�����书������ʽ������invent <�Ѵ��书>\n");
	} 

	if( me->is_busy() )
		return notify_fail("�㻹����æ����ͷ������˵�ɣ�\n");	 

	if( where->query("pigging") )
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");
		
	if( !where->query("no_fight") )
		return notify_fail("������չأ���̫��ȫ�ɣ�\n");

	if( !where->query("sleep_room") )
		return notify_fail("�����һ���ܹ���Ϣ�ĵط��չء�\n");
		
	if( !ultrap(me))
		return notify_fail("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n");
       
	if( me->query("potential") < 10000 )
		return notify_fail("���Ǳ�ܲ�����û���չ����С�\n");

	if( (int)me->query("qi") * 100 / me->query("max_qi") < 90 )
		return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

	if( (int)me->query("jing") * 100 / me->query("max_jing") < 90 )
		return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

	if( (int)me->query("max_neili") < 4000 )
		return notify_fail("������������в��㣬����Ŀǰ������"
				   "���г�ʱ��ıչ�������\n");

	if( (int)me->query("neili") * 100 / me->query("max_neili") < 90 )
		return notify_fail("�����ڵ�����̫���ˣ��޷����ıչء�\n");
		
	if( !mapp(skills_map = me->query_skills() ) || sizeof(skills_map) < 1 )
		return notify_fail("�㻹����ȥѧ�㹦�������ɡ�\n");

	if( undefinedp(skills_map[arg]) || skills_map[arg] < 1 )
		return notify_fail("����������" + valid_types[arg] + "�����ᣬ�Ӻ�̸��\n");

	if( skills_map[arg] < NEED_LVL )
		return notify_fail("�㻹�Ǵ��" + valid_types[arg] + "�Ļ������ɡ�\n");

	if( objectp( weapon = me->query_temp("weapon") ) ) {

		if( member_array(arg, weapon_types) == -1 && arg != "dodge" )
			return notify_fail("�������ֲ����Դ�" + valid_types[arg] + "��\n");

		if( member_array(arg, weapon_types) != -1 && weapon->query("skill_type") != arg )
			return notify_fail("����ʹ�õ��������ԣ��޷��Դ�" + valid_types[arg] + "��\n");
	} else if( member_array(arg, weapon_types) != -1 )
			return notify_fail("����������������ܿ�ʼ�Դ�" + valid_types[arg] + "��\n");

	skills = keys(skills_map);

	foreach( string sk_tmp in skills ) {
		if( SKILL_D(sk_tmp)->valid_enable(arg) ) {
			mut_skills += ({ sk_tmp });
		}
	}

//	if( sizeof(mut_skills) < 3 )
//		return notify_fail("���" + valid_types[arg] + "��Ϊ�������㲩����ȥ��ѧϰѧϰ��\n");

	mut_skills = filter_array(mut_skills, (: $(skills_map)[$1] >= NEED_LVL :));

//	if( sizeof(mut_skills) < 4 )
//		return notify_fail("����" + valid_types[arg] + "�������Ϊ���������\n");
	
	me->delete_temp("invent");
	
	if( stringp(invent_skill) )
	{
		me->set_temp("invent/spe_skill/skill_z_number", skill_t_number(invent_skill) + 1);			
		if (skill_t_number(invent_skill) + 1 >= 10)
			return notify_fail("���" + to_chinese(invent_skill) + 
					   "��ʽ�Ѿ����˼��ޣ��޷����Դ�����ʽ��\n");
		
		message_vision("$N��ϥ���£���ʼ��˼ڤ�룬ר�ĵ��Դ�" + to_chinese(invent_skill) + "��\n", me);	      
	}
	else    message_vision("$N��ϥ���£���ʼ��˼ڤ�룬ר�ĵ��Դ�һ��" + valid_types[arg] + "��\n", me);

	me->set_temp("invent/skill", arg);
	me->set_temp("invent/spe_skill/skill", arg); 
	me->set_temp("invent/mut_skills", mut_skills);	
	
	if( stringp(invent_skill) )
		me->set_temp("invent/invent_skill", invent_skill);
	
	me->set_short_desc("����ȫ���ע���Դ�" + valid_types[arg] + "��");

	me->start_busy(bind((:call_other, __FILE__, "inventing" :), me),
		       bind((:call_other, __FILE__, "halt_inventing" :), me));

	CHANNEL_D->do_channel(this_object(), "rumor",
			      sprintf("%s(%s)��ʼ�չ��Դ�%s��\n",
			      me->name(1), me->query("id"), stringp(invent_skill) ? 
			      (to_chinese(invent_skill) + "����ʽ") : valid_types[arg]));
	return 1;
}


int inventing(object me)
{
	int     pot, max, i;
	string  skill, *mut_skills, *skills_tmp, skills,
		skill_name, msg = "", *msgs = ({});
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	pot = me->query("potential");
	if( pot <= 0 )
	{
		tell_object(me, "���Ǳ�ܺľ���ȴһ������ʧ����վ�ˡ�\n");
		message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
		me->set_short_desc(0);
		return 0;
	}

	if( me->add("learned_points", 100 + random(100)) > pot)
		me->set("learned_points", pot);

	if( random(5) != 0) return 1;

	skill = me->query_temp("invent/skill");
	mut_skills = me->query_temp("invent/mut_skills");

	if( random(10) == 1 ) {
		string *chinese_skills = ({});

		foreach(string mut_skill in mut_skills) {
			chinese_skills += ({ to_chinese(mut_skill)});
		}
		
		if( stringp( skills = me->query_temp("invent/invent_skill") ) )
		{
			s_skill["skill_e_name"] = skills;
			s_skill["skill_c_name"] = to_chinese(skills);			
						
			message_sort("��Ȼ��$N�����Թ�������ʽ����" + 
				sprintf( HIG"%s" NOR "�Լ�" HIG "%s"NOR, 
				implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "��" HIG), 
				chinese_skills[sizeof(chinese_skills)-1])
				+ "��" + chinese_number(sizeof(mut_skills)) + "���书����ʽ�϶�Ϊ"
				"һ��Ϊ" + to_chinese(skills) + "������ʽ��\n", me);
			
			me->clear_written();				   
			tell_object(me, HIC "\n\n���" + to_chinese(skills) + "����ʽ�������(����: " NOR HIY "����" NOR HIC "):" NOR);	  
			me->set_short_desc(0);			
			
			input_to( "get_z_c_name", me );
			return 0;
		}       
		message_sort("��Ȼ��$N�����Թ�������ʽ����" + 
				sprintf( HIG"%s" NOR "�Լ�" HIG "%s"NOR, 
				implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "��" HIG), 
				chinese_skills[sizeof(chinese_skills)-1])
				+ "��" + chinese_number(sizeof(mut_skills)) + "���书�϶�Ϊһ��\n", me);

		me->clear_written();
		tell_object(me, HIW"\n\n\n���Դ�����һ��" + valid_types[skill] + "��"NOR"\n"
				"�����Ϊ����" + valid_types[skill] + "ȡһ������\n\n"
				HIY"��ʽ��"HIC"<Ӣ����> <������>\n"NOR"\n"
				"�����룺wuyou ����\n"
				"ϵͳ�����һ������"HIR + type_name[skill] + NOR "(wuyou-"
				HIR + skill + NOR")��" + valid_types[skill] + "\n"
				HIW"����ɧ���Ի��ŵ����֣����򽫻ᱻɾ����"NOR"\n"
				"�����룺");
		me->set_short_desc(0);		       
		input_to( "input_skill_name", me );
		return 0;
	}

	skills_tmp = copy(mut_skills);

	max = 2 + random(sizeof(mut_skills)-2);
	if ( max > 5 ) max = 5;

	if( max < sizeof(mut_skills) ) {
		for( i = max; i < sizeof(mut_skills); i++ ) {
			skills_tmp -= ({ skills_tmp[random(sizeof(skills_tmp))] });
		}
	}

	foreach(string sk_tmp in skills_tmp) {
		msgs += ({ get_skill_name(me, sk_tmp) });
	}

	msg = msga[random(sizeof(msga))] + sprintf("%s" NOR "�Լ�%s", 
	      implode(msgs[0..sizeof(msgs)-2], NOR "��"), msgs[sizeof(msgs)-1])
	      + NOR + msgb[random(sizeof(msgb))] + ""NOR"\n";

	message_sort(msg, me);

	return 1;
}

int halt_inventing(object me)
{
	me->set_short_desc(0);
	me->delete_temp("invent");
	tell_object(me, "����ֹ���Դ���\n");
	message_vision(HIY "$N" HIY "����վ�������������ʧ����"NOR"\n", me);
	return 1;
}

string get_skill_name(object me, string skill)
{
	mapping actions;
	string  skill_name, action;
	int     a, b;

	if( !find_object(SKILL_D(skill)) && !load_object(SKILL_D(skill)) )
		return HIG + to_chinese(skill);

	if( !mapp( actions = SKILL_D(skill)->query_action(me, me->query_temp("weapon")) ) )
		return HIG + to_chinese(skill);

	if( !undefinedp(actions["skill_name"]) )
		return HIG + actions["skill_name"];

	if( undefinedp(actions["action"]) )
		return HIG + to_chinese(skill);

	action = actions["action"];

	if( strsrch(action, "��") != -1 && strsrch(action, "��") != -1 ) {
		a = strsrch(action, "��");
		b = strsrch(action, "��");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"��һ��"YEL:"�е�"YEL) + skill_name + NOR;
	} else if( strsrch(action, "��") != -1 && strsrch(action, "��") != -1 ) {
		a = strsrch(action, "��");
		b = strsrch(action, "��");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"��һ��"YEL:"�е�"YEL) + skill_name + NOR;
	} else if( strsrch(action, "��") != -1 && strsrch(action, "��") != -1 ) {
		a = strsrch(action, "��");
		b = strsrch(action, "��");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"��һ��"YEL:"�е�"YEL) + skill_name + NOR;
	} else return HIG + to_chinese(skill);
}

int skill_t_number(string e_name)
{
	/*
	string *list;
	int    i, flag, total_z_number;

	if( !SKILL_D(e_name)->is_invent_skill() )
		return 0;
		
	list = explode(read_file(SKILL_D(e_name) + SYC), "\n");

	for( i = sizeof(list) - 1; i > 0; i-- )
	{
		if (! stringp(list[i])) continue;
		if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
		{
			flag = 1;
			break;
		}
	}
	
	if( !flag )
	{
		write(HIR "���ܳ����쳣�ˣ�������ʦ���������"NOR"\n");  
		return 0;    
	}
		
	return total_z_number;
	*/
	return sizeof(SKILL_D(e_name)->query_actions());
}

void input_skill_name(string arg, object me)
{
	string  c_name, e_name, skill;
	int     i;
	object  invent;
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	       
	if( sscanf(arg, "%s %s", arg, c_name) != 2 )
	{
		tell_object(me, "�Բ������ã�<Ӣ����> <������> �ĸ�ʽ���롣\n���������룺");
		input_to((: input_skill_name :), me);
		return;
	}
	
	if ((strlen(arg) < 3) || (strlen(arg) > 10))
	{
		tell_object(me, "�Բ���Ӣ���������� 3 �� 10 ��Ӣ����ĸ��\n���������룺");
		input_to((: input_skill_name :), me);
		return;
	}

	while (i--)
	{
		if (arg[i] < 'a' || arg[i] > 'z' )
		{
			tell_object(me, "�Բ���Ӣ����ֻ����Ӣ����ĸ��\n���������룺");
			input_to((: input_skill_name :), me);
			return;
		}
	}
	
	skill = temp["invent"]["skill"];
	arg = arg + "-" + skill;
	e_name = arg;

	if( file_size(SKILL_D(arg) + SYC) > 0 
	 || get_object(SKILL_D(arg)) 
	 || arg != to_chinese(arg) ) {
			tell_object(me, "�Բ����Ѿ���("+ e_name +")�����书���ڡ�\n���������룺");
			input_to((: input_skill_name :), me);
			return;
	}

	if( !is_chinese(c_name) ) {
			tell_object(me, "�Բ������á����ġ�����������\n���������룺");
			input_to((: input_skill_name :), me);
			return;
	}

	if (member_array(c_name, banned_name) % 2 == 0)
	{
		tell_object(me, "�Բ����������ƻ���������˵����š�\n���������룺");
		input_to((: input_skill_name :), me);
		return;
	}

	if( strlen(c_name) > 20 ) {
		tell_object(me, "�Բ��������õ�������̫������ѡһ����տһ������֡�\n���������룺");
		input_to((: input_skill_name :), me);
		return;
	}

	c_name += type_name[skill];
	s_skill["skill_e_name"] = e_name;
	s_skill["skill_c_name"] = c_name;
	
	if( CHINESE_D->find_skill(c_name) ) {
			tell_object(me, "�Բ����Ѿ���[" + c_name + "]�����书���ڡ�\n���������룺");
			input_to((: input_skill_name :), me);
			return;
	}


	tell_object(me, HIW"\n\n\n���ɹ����Դ�����" HIG + c_name + "(" + e_name + ")" HIW "����" + valid_types[skill]
				 + NOR "\n������Ϊ����书���һ��������\n"
				 "----------------------------------------------------------------\n\n"
				 + sort_msg("�磺" + c_name + "�Ǵ���" + me->name(1) + "�ľ���" + valid_types[skill] + 
					    "����ʽ����ֱǰ���󿪴��أ������ͰԵ������ƣ���������ʮ������"
					    "Χ��" + me->name(1) + "��ʱ���������Σ����" + me->name(1)
					    + "��ǧ��һ��֮��ʹ�������书����ʱ���Ʊ�ɫ������Ϊ�ġ���\n\n")
				 + "----------------------------------------------------------------\n\n"
				 + "�����룺");
	me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
}

void describe_done(object me, string skill, string e_name, string c_name, string msg)
{
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	if( !stringp( msg ) || msg == "" )
		tell_object(me, "������Ϊ�����书���������\n");
	else {
		if( strlen(msg) > 1000 ) {
			tell_object(me, "���趨������̫���ˣ����趨һ�������������\n");
			me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
			return;
		}
	}
	
	s_skill["skill_result"] = msg; 
	s_skill["skill_z_number"] = 1;
	
	tell_object(me, HIC "\n\n���" + c_name + "��ʽ�������(����: " NOR HIY "����" NOR HIC "):" NOR);	 
	input_to( "get_z_c_name", me );
}

void skill_init_header(object me, string e_name)
{
	string  header;
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	e_name += SYC;
	
	header =  "// This is player's own skill (Write by Lonely@nt2)\n";
	header += "// Create by " + me->query("name") + "(" + capitalize(geteuid(me)) + ") at " + ctime(time()) + "\n";
	header += "// " + s_skill["skill_c_name"] + "(" + e_name + ")\n";
	header += @HEADER

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
HEADER;
	
	write_file(SKILL_D(e_name), header, 1);
}

void get_z_c_name(string yn, object ob)
{
	mapping temp, s_skill;
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
		
	if( yn == "" ) {
		tell_object(ob, HIC "\n\n���" + s_skill["skill_c_name"] + "��ʽ�������(����: " NOR HIY "����" NOR HIC "):" NOR);   
		input_to( (: get_z_c_name :), ob );
		return;
	}

	switch( yn[0] ) {
	case 'E':
	case 'Q':
		ob->delete_temp("invent");
		tell_object(ob, "����������Դ��书��\n");
		return;
	}


	if( !is_chinese(yn) ) {
		tell_object(ob, "��ʽ���ƣ�");
		input_to( (: get_z_c_name :), ob );
		return;
	}
	
	s_skill["skill_name"] = yn;

	tell_object(ob, HIR "\nע������: $N ������ $n ������� $l ��������λ $w ����������� "NOR"\n");
	tell_object(ob, BLINK WHT "����:(ȭ����)"NOR"\n");
	tell_object(ob, "$N���۽��죬�Ƚż��أ�һʽ��ͬ���Ȫ���������İ�ס$n���������������\n\n");
	tell_object(ob, BLINK WHT "������:(��������)"NOR"\n"); 
	tell_object(ob, "$N����һԾ������$w,��ʱһ�С�б�����¡���׼$n��ĳ��λбб�̳�һ��\n\n");
	tell_object(ob, "��ʽ������");

	input_to("get_z_c_action", ob);

}

void get_z_c_action(string yn, object ob)
{
	string  skill_type;
	mapping temp, s_skill;
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	if (yn == "") 
	{
		tell_object(ob, HIR "\nע������: $N ������ $n ������� $l ��������λ $w ����������� "NOR"\n");
		tell_object(ob, BLINK WHT "����:(ȭ����)"NOR"\n");
		tell_object(ob, "\t$N���۽��죬�Ƚż��أ�һʽ��ͬ���Ȫ���������İ�ס$n���������������\n\n");
		tell_object(ob, BLINK WHT "������:(��������)"NOR"\n"); 
		tell_object(ob, "\t$N����һԾ������$w,��ʱһ�С�б�����¡���׼$n��ĳ��λбб�̳�һ��\n\n");
		tell_object(ob, "��ʽ������");
		input_to((: get_z_c_action :), ob);
		return;
	}
	
	// �˳��Դ�
	switch(yn[0])
	{
	case 'e':
	case 'q':
		ob->delete_temp("invent");
		tell_object(ob, "����������Դ��书��ʽ��\n");
		return;
	}
	
	skill_type = temp["invent"]["skill"];
	
	s_skill["action"] = color_filter(yn);
	s_skill["action"] = replace_string(s_skill["action"], " ", "");
	s_skill["action"] = replace_string(s_skill["action"], "��", "$N");
	s_skill["action"] = replace_string(s_skill["action"], "��è", "$n");	       
	s_skill["action"] = replace_string(s_skill["action"], "ĳ��λ", "$l");	      

	if ( member_array(skill_type, weapon_types) != -1 )
		s_skill["action"] = replace_string(s_skill["action"], "����", "$w");
		
       // �Դ��乤�����������ޡ�����ȼ������̾���
	s_skill["attack"] = ob->query("level") + ob->query("int") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;			       
	s_skill["damage"] = ob->query("level") + ob->query("str") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;
	s_skill["force"]  = ob->query("level") + ob->query("con") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +    
			    ob->query_skill("martial-cognize", 1) / 10;										    
	s_skill["dodge"]  = ob->query("level") + ob->query("dex") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 + 
			    ob->query_skill("martial-cognize", 1) / 10;								
	s_skill["parry"]  = ob->query("level") + ob->query("con") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;

	switch(skill_type){
	case "unarmed":
		s_skill["damage_type"] = "����";
		break;
	case "sword":
	case "spin":
		s_skill["damage_type"] = "����";
		break;
	case "blade":
		s_skill["damage_type"] = "����";
		break;
	case "strike":
		s_skill["damage_type"] = "����";
		break;
	default:
		s_skill["damage_type"] = "����";
		break;
	}			     
	s_skill["lvl"] = spe_skill_level[s_skill["skill_z_number"] - 1];				
	
	if (s_skill["skill_z_number"] == 1)			
		tell_object(ob, HIR "\n���Դ���һ��" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + ")"NOR"\n"
				HIY "�书���ͣ�" NOR HIC + valid_types[skill_type] + ""NOR"\n"
				HIY "�书������"NOR"\n" HIC + s_skill["skill_result"] + ""NOR"\n"
				HIY "�������ƣ�" NOR HIC + s_skill["skill_name"] + ""NOR"\n"
				HIY "����������" NOR HIC + s_skill["action"] + ""NOR"\n"
				HIY "���й�����" NOR HIC + s_skill["attack"] + ""NOR"\n"
				HIY "�����˺���" NOR HIC + s_skill["damage"] + ""NOR"\n"
				HIY "�����˺���" NOR HIC + s_skill["force"] + ""NOR"\n"
				HIY "�����мܣ�" NOR HIC + s_skill["parry"] + ""NOR"\n"
				HIY "���ж�����" NOR HIC + s_skill["dodge"] + ""NOR"\n"
				HIR "��ȷ����(Y/N)" NOR);
	else
		tell_object(ob, HIR "���Դ���һ��" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + 
				HIR ")�ĵ�" + chinese_number(s_skill["skill_z_number"]) + "��"NOR"\n"
				HIY "�������ƣ�" NOR HIC + s_skill["skill_name"] + ""NOR"\n"
				HIY "����������" NOR HIC + s_skill["action"] + ""NOR"\n"
				HIY "���й�����" NOR HIC + s_skill["attack"] + ""NOR"\n"
				HIY "�����˺���" NOR HIC + s_skill["damage"] + ""NOR"\n"
				HIY "�����˺���" NOR HIC + s_skill["force"] + ""NOR"\n"
				HIY "�����мܣ�" NOR HIC + s_skill["parry"] + ""NOR"\n"
				HIY "���ж�����" NOR HIC + s_skill["dodge"] + ""NOR"\n"
				HIR "��ȷ����(Y/N)" NOR); 

	input_to("decide_input", ob, skill_type, s_skill["skill_e_name"], s_skill["skill_c_name"]);
}

void decide_input(string arg, object me, string skill, string e_name, string c_name)
{
	object  ob;
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
		
	if( arg == "y" || arg == "Y" ) {
		if( s_skill["skill_z_number"] == 1 ) {
			if( objectp( ob = get_object(SKILL_D(e_name)) ) ) {
				me->delete_temp("invent");
				tell_object(me, "BUG������ϵ��ʦ��\n");
				return;
			}
		
			finish_write_skill(me, e_name);

			log_file("INVENT", sprintf("%s(%s) %s(%s): %d (%s)\n",
					   me->query("name"),
					   me->query("id"),
					   c_name,
					   e_name,
					   s_skill["skill_z_number"],
					   ctime(time())));

			if( get_object(SKILL_D(e_name)) ) {
				CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s(%s)����ƽ��ѧ��" + chinese_number(sizeof(me->query_temp("invent/mut_skills")))
						+ "��" + valid_types[skill] + "�϶�Ϊһ���Դ���һ�׾�����" NOR HIW
						+ "��" + c_name + "��" NOR HIM "���Ӵ˽���"
						+ valid_types[skill] + "��ȫ�¾��� ��" NOR,
						me->name(1), me->query("id")));
				me->force_me("chat* admire2 " + me->query("id"));
			
				CHINESE_D->add_translate(e_name, c_name);			
					
				me->set("invent/" + skill, e_name);
				me->set_skill(e_name, 100);
				me->delete_temp("invent");
				me->save();
			}

		} else {
			if( !objectp( ob = get_object(SKILL_D(e_name)) ) ) {
				me->delete_temp("invent");
				tell_object(me, "BUG������ϵ��ʦ��\n");
				return;
			}			
			destruct(ob);
			finish_write_skill(me, e_name);
			get_object(SKILL_D(e_name));
			log_file("INVENT", sprintf("%s(%s) %s(%s): %d (%s)\n",
					   me->query("name"),
					   me->query("id"),
					   c_name,
					   e_name,
					   s_skill["skill_z_number"],
					   ctime(time())));
					   
			CHANNEL_D->do_channel(this_object(), "rumor",
					   sprintf("%s(%s)����ƽ��ѧ�ں����գ�Ϊ" NOR HIW + "��" + c_name + "��" NOR
					   HIM "�����µ���ʽ" NOR HIC + "��" + s_skill["skill_name"] + "��" NOR + HIM "��" , 
					   me->name(1), me->query("id")));
						
			me->force_me("chat* admire2 " + me->query("id"));
			me->delete_temp("invent");
			me->save();
		} 


	} else {
		if( s_skill["skill_z_number"] == 1 ) {
			tell_object(me, HIW"���������룡"
					HIY"��ʽ��"HIC"<Ӣ����> <������>\n"NOR"\n"
					"�����룺wuyou ����\n"
					"ϵͳ�����һ������"HIR + type_name[skill] + NOR "(wuyou-"
					HIR + skill + NOR")�Ľ���\n"
					HIW"����ɧ���Ի��ŵ�����"NOR"\n"
					"�����룺");
			input_to("input_skill_name", me, skill);
		} else {
			tell_object(me, HIC "\n\n���" + c_name + "����ʽ�������(����: " NOR HIY "����" NOR HIC "):" NOR);	  
			input_to( "get_z_c_name", me ); 
		}		       
	}
}

void finish_write_skill(object ob, string skill)
{
	mapping temp, s_skill;
	string  action;
	string  file, *list;
	string  content;
	int     total_z_number, i, flag;
	string  *list2;
	string  header2;
	string  result;
	string  skill_type;	
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	skill_type = temp["invent"]["skill"];
	header2 = "";
	result = "";
	content = "";
	action = "";  

	if( s_skill["skill_z_number"] == 1 )
		skill_init_header(ob, skill);      
	  
	action += "\n([      " + SYN + 
		  "action" + SYN + " : " + SYN + s_skill["action"] + SYN + ",\n\t" + SYN + 
		  "attack" + SYN + " : " +  s_skill["attack"] + ",\n\t" + SYN + 
		  "damage" + SYN + " : " +  s_skill["damage"] + ",\n\t" + SYN + 
		  "force" + SYN + " : " +  s_skill["force"] + ",\n\t" + SYN +
		  "dodge" + SYN + " : " + s_skill["dodge"] + ",\n\t" + SYN + 
		  "parry" + SYN + " : " + s_skill["parry"] + ",\n\t" + SYN + 
		  "lvl" + SYN + " : " + s_skill["lvl"] + ",\n\t" + SYN + 
		  "damage_type" + SYN + " : " + SYN + s_skill["damage_type"] + SYN + ",\n\t" + SYN + 
		  "skill_name" + SYN + " : " + SYN + s_skill["skill_name"] + SYN +
		  "\n ])," +
		  "\n// ZHAOSHI : " + s_skill["skill_z_number"];
	action += "\n});\n";

	file = read_file(SKILL_D(skill + SYC));
	if( (int)file != 0 )
		list = explode(file, "\n");

	if( skill_type == "unarmed" 
		|| skill_type == "strike"
		|| skill_type == "finger" )
		header2 = read_file(SKILL_MODEL_UNARMED);
	else if( skill_type=="sword" 
		|| skill_type == "blade"
		|| skill_type=="spear"
		|| skill_type=="hammer"
		|| skill_type=="whip" )
		header2 = read_file(SKILL_MODEL_WEAPON);
	else 
		header2 = read_file(SKILL_MODEL_DEFAULT);

	list2 = explode(header2, "\n");
	for( i = 0; i < sizeof(list2); i++ ) {
		list2[i]= replace_string(list2[i], "SKILL_EN_NAME", 
			  SYN + skill + SYN);
		list2[i]= replace_string(list2[i], "SKILL_CH_NAME", 
			  SYN + s_skill["skill_c_name"] + SYN);
		list2[i]= replace_string(list2[i], "SKILL_BASE_NAME", 
			  SYN + skill_type + SYN);
	}
	
	result += implode(list2, "\n");

	for( i = sizeof(list) - 1; i > 0; i-- ) {
		if (! stringp(list[i])) continue;
		if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
		{
			flag = 1;
			break;
		}
	}
	
	if( !flag )
	{
		tell_object(ob, HIR "���ܳ����쳣�ˣ�������ʦ���������"NOR"\n");  
		return;    
	}

	content =  implode(list[0..i-1], "\n");
	content += "\n// ZHAOSHI : " + (string)total_z_number;
	content += action;
	write_file(SKILL_D(skill) + SYC, content, 1);	
	write_file(SKILL_D(skill) + SYC, "\n" + result);
	
	if( stringp(s_skill["skill_result"]) ) {
		s_skill["skill_result"] = replace_string(s_skill["skill_result"], "\n", "");
		s_skill["skill_result"] = sort_msg(s_skill["skill_result"]);
	
		content = @CODE
string query_description()
{
CODE;
		content += "\treturn\n \"" + s_skill["skill_result"] + "\" ; \n}\n";
	
		write_file(SKILL_D(skill) + SYC, "\n" + content); 
	}       
}

int help(object me)
{
	write(@HELP
					 
ָ���ʽ: invent		�鿴�Լ��Դ��书�����
	  invent ?	      �鿴Ŀǰ�����Դ����书����
	  invent <�����书>     �Դ�һ���书
	  invent <�Ѵ��书>     �����Դ�һ���书����ʽ
	  invent <�����书> ?   �鿴�û����书���Ѵ��书
	  invent <�����书> d   ɾ���û����书���Ѵ��书

���������п���һ����ʦ�ߣ���������ѧ���ܽἺ֮��ѧ������
�ڻ����֮�����������������Ⱥ��ߡ���ѧ��Ȼ����Դ��һ����
��������ѧ��֮����֮��ͬ��ȴ��ͬһ�����в�ͬ������ˣ�
���ֲű������Ѥ����ʡ�Ȼ�������������е���Ϫ��������
�£���Ҫ�ķ�������Ѫ���������п��ܶ���һ�ģ���������δ��
�롣 

HELP );
	return 1;
}
