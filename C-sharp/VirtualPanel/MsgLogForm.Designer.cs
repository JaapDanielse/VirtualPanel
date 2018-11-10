namespace VirtualPanel
{
    partial class MsgLogForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MsgLogForm));
            this.btn_reset = new System.Windows.Forms.Button();
            this.LogFileButton = new System.Windows.Forms.Button();
            this.LogClearButton = new System.Windows.Forms.Button();
            this.LogHoldButton = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.logmonitor = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // btn_reset
            // 
            this.btn_reset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_reset.Location = new System.Drawing.Point(12, 206);
            this.btn_reset.Name = "btn_reset";
            this.btn_reset.Size = new System.Drawing.Size(95, 23);
            this.btn_reset.TabIndex = 3;
            this.btn_reset.Text = "arduino reset";
            this.btn_reset.UseVisualStyleBackColor = true;
            this.btn_reset.Click += new System.EventHandler(this.btn_reset_Click);
            // 
            // LogFileButton
            // 
            this.LogFileButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LogFileButton.Location = new System.Drawing.Point(414, 205);
            this.LogFileButton.Name = "LogFileButton";
            this.LogFileButton.Size = new System.Drawing.Size(80, 24);
            this.LogFileButton.TabIndex = 4;
            this.LogFileButton.Text = "file";
            this.LogFileButton.UseVisualStyleBackColor = true;
            this.LogFileButton.Click += new System.EventHandler(this.LogFileButton_Click);
            // 
            // LogClearButton
            // 
            this.LogClearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LogClearButton.Location = new System.Drawing.Point(330, 205);
            this.LogClearButton.Name = "LogClearButton";
            this.LogClearButton.Size = new System.Drawing.Size(80, 24);
            this.LogClearButton.TabIndex = 5;
            this.LogClearButton.Text = "clear";
            this.LogClearButton.UseVisualStyleBackColor = true;
            this.LogClearButton.Click += new System.EventHandler(this.LogClearButton_Click);
            // 
            // LogHoldButton
            // 
            this.LogHoldButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LogHoldButton.Location = new System.Drawing.Point(244, 205);
            this.LogHoldButton.Name = "LogHoldButton";
            this.LogHoldButton.Size = new System.Drawing.Size(80, 24);
            this.LogHoldButton.TabIndex = 6;
            this.LogHoldButton.Text = "hold";
            this.LogHoldButton.UseVisualStyleBackColor = true;
            this.LogHoldButton.Click += new System.EventHandler(this.LogHoldButton_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "txt";
            this.saveFileDialog1.FileName = "PanelOneLog";
            this.saveFileDialog1.Filter = "\"Txt files (*.txt)|*.txt|All files (*.*)|*.*\"";
            this.saveFileDialog1.Title = "Save log file";
            // 
            // logmonitor
            // 
            this.logmonitor.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.logmonitor.ForeColor = System.Drawing.SystemColors.WindowText;
            this.logmonitor.Location = new System.Drawing.Point(12, 12);
            this.logmonitor.Name = "logmonitor";
            this.logmonitor.ReadOnly = true;
            this.logmonitor.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.logmonitor.Size = new System.Drawing.Size(479, 180);
            this.logmonitor.TabIndex = 8;
            this.logmonitor.Text = "";
            // 
            // MsgLogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(503, 241);
            this.Controls.Add(this.logmonitor);
            this.Controls.Add(this.LogHoldButton);
            this.Controls.Add(this.LogClearButton);
            this.Controls.Add(this.LogFileButton);
            this.Controls.Add(this.btn_reset);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MsgLogForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Message Log";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SettingsForm_FormClosing);
            this.ResumeLayout(false);

        }

        #endregion
        internal System.Windows.Forms.Button btn_reset;
        internal System.Windows.Forms.Button LogFileButton;
        internal System.Windows.Forms.Button LogClearButton;
        internal System.Windows.Forms.Button LogHoldButton;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.RichTextBox logmonitor;
    }
}