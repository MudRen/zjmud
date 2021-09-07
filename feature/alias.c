// alias.c

#include <ansi.h>
#include <dbase.h>
#include <name.h>
#include <message.h>

#define MAX_ALIASES	     50
mapping alias;

// ��¼�û��������Ϣ����
static string *history, last_input, orginal_input;
static int direct_command;

// ������������(�Ѿ�����ALIAS����)
string query_last_input() { return last_input; }

// ��������ԭʼ�ַ���(�Ѿ���������ȷ�ϣ�/��//��ͷ)
string query_orginal_input() { return orginal_input; }

// �Ƿ��ǿ�������(��/��//��ͷ)
int is_direct_command() { return direct_command; }

string process_input(string str)
{
	string *args, cmd, argstr;
	object me;
	int i, j;

	me = this_object();
	notify_fail("ʲô��\n");
	clear_written();
	if (! living(me)) return "";

	// ��¼��ԭʼ������
	if (str[0] == '/')
	{
		direct_command = 1;
		if (str[1] == '/') str = str[2..<1]; else
				   str = str[1..<1];
	} else
		direct_command = 0;
	orginal_input = str;
	
	// attach system ?
	if (me->is_attach_system())
	{
		me->detach_system();
		tell_object(me, HIR "�û���ֹ�˵�ǰִ�еĽ��̡�"NOR"\n");
	}

	if (str == "") return str;

	if (! wizardp(me))
	{
		if (me->reject_command())
		{
			int cq, cj;

			// �ε��Ժ�Ҫ��֤qi/jing����
			cq = query("qi");
			cj = query("jing");

			// ȷ��qi/jing��С���㣬���ָ������ԩ��
			if (cq < 1) cq = 0;
			if (cj < 1) cj = 0;

			// ��Ҫ��֤��������������ɫ����

			//set("jing", 0);
			//me->receive_damage("jing", 0);

			message_vision(BLU "\n��պ�Ȼ�����˼�����Ц����ʱ�������ܲ���һ��" HIW "����" BLU "���������"NOR"\n", me);
 
			//me->unconcious();				

			// �ָ��ε�ǰ��qi/jing
			//set("qi", cq);
			//set("jing", cj);

			// ȷ����Ч��qi/jing��С���㣬�����
			// Ϊָ������ԩ����
			if (query("eff_qi") < 1) set("eff_qi", 0);
			if (query("eff_jing") < 1) set("eff_jing", 0);

			message_vision(HIY "ֻ��$N����һ������ð������ʱ����һ���������......"NOR"\n", me);

                        tell_object(me,"����ʹ������ǧ�ﴫ�����������ָ����࣬slow down"NOR"\n"); 

	                if (me->is_busy())
                             me->add_busy(2);
                        else me->start_busy(2);

			return "";
		}
	}

	if (mapp(alias))
	{
		if (! undefinedp(alias[str]))
		{
			str = replace_string(alias[str], "$*", "");
		} else
		if (sscanf(str, "%s %s", cmd, argstr) == 2 && ! undefinedp(alias[cmd]))
		{
			cmd = replace_string(alias[cmd], "$*", argstr);
			args = explode(argstr, " ");
			if ((j = sizeof(args)))
				for (i = 0; i < j; i++)
					cmd = replace_string(cmd, "$" + (i + 1), args[i]);
			str = cmd;
		}
	}

	last_input = (string)ALIAS_D->process_global_alias(str);
	log_command(last_input);
	return last_input;
}

int set_alias(string verb, string replace)
{
	if (! replace)
	{
		if (mapp(alias)) map_delete(alias, verb);
		return 1;
	} else
	{
		if (! mapp(alias)) alias = ([ verb : replace ]);
		else if (sizeof(alias) > MAX_ALIASES)
			return notify_fail("���趨�� alias ̫���ˣ�����ɾ��һЩ�����õġ�\n");
		else alias[verb] = replace;
		return 1;
	}
}

mapping query_all_alias()
{
	return alias;
}
